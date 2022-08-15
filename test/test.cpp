#include <gtest/gtest.h> // googletest header file
#include "libusb-1.0/libusb.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

// using std::string;

// const char *actualValTrue  = "hello gtest";
// const char *actualValFalse = "hello world";
// const char *expectVal      = "hello gtest";

// TEST(StrCompare, CStrEqual) {
//     EXPECT_STREQ(expectVal, actualValTrue);
// }

// TEST(StrCompare, CStrNotEqual) {
//     EXPECT_STREQ(expectVal, actualValTrue);
// }

static int count = 0;
int status_flag = -1;

int hotplug_callback(struct libusb_context *ctx, struct libusb_device *dev,
                     libusb_hotplug_event event, void *user_data) {
  static libusb_device_handle *dev_handle = NULL;
  struct libusb_device_descriptor desc;
  int rc;
  printf("hotplug_callback started\n");
  (void)libusb_get_device_descriptor(dev, &desc);

  

  if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event) {
    rc = libusb_open(dev, &dev_handle);
    
    EXPECT_EQ(rc,-3);
    
    
    printf("...USB Device Connected...\n");
    
    status_flag = 1;
    printf("rc: %d\n",rc);
    //EXPECT_EQ(status_flag,1);
    
    if (LIBUSB_SUCCESS != rc) {
      printf("Could not open USB device\n");
    }
  } else if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event) {
      printf("...USB Device Removed...\n");
      status_flag = 0;
      
      EXPECT_EQ(status_flag,0);
      
    if (dev_handle) {
      libusb_close(dev_handle);
      dev_handle = NULL;
    }
    
    //EXPECT_EQ(&dev_handle,NULL); 
    
  } else {
    printf("Unhandled event %d\n", event);
  }
  count++;
  printf("count: %d\n",count);

  return 0;
}

TEST(testMath, myTest)
{
	printf("Main started\n");
	libusb_hotplug_callback_handle callback_handle;
	int rc;
	int test;
	printf("libusb callback handle passed...\n");
	libusb_init(NULL);

	rc = libusb_hotplug_register_callback(NULL,static_cast<libusb_hotplug_event> (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED |
		LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT), LIBUSB_HOTPLUG_NO_FLAGS, LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
		LIBUSB_HOTPLUG_MATCH_ANY, hotplug_callback, NULL, &callback_handle);
	printf("libusb register passed\n");

	ASSERT_EQ(LIBUSB_SUCCESS,rc);
	
	printf("stage at while loop...\n");

	EXPECT_EQ(libusb_handle_events_completed(NULL, NULL),0);

	libusb_hotplug_deregister_callback(NULL, callback_handle);
	libusb_exit(NULL);
	printf("Existing main function\n");
}
