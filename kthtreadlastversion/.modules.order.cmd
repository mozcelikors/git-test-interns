cmd_/home/sahin/chardevice/modules.order := {   echo /home/sahin/chardevice/kernel_thread.ko; :; } | awk '!x[$$0]++' - > /home/sahin/chardevice/modules.order
