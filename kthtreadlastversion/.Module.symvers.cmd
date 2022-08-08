cmd_/home/sahin/chardevice/Module.symvers := sed 's/\.ko$$/\.o/' /home/sahin/chardevice/modules.order | scripts/mod/modpost -m -a  -o /home/sahin/chardevice/Module.symvers -e -i Module.symvers   -T -
