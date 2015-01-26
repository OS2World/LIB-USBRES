USBRES02.ZIP - USB Resource Manager for OS/2 (and eComStation)
==============================================================

May be freely used and exchanged, as long as it is not modified. You may
use this product solely at your own risk. I cannot be held responsible for
any damages occurring due to your using this product. You may not lease,
rent or sell this product to any other party. Have fun.

The current sources are at netlabs in my private branch:

https://svn.netlabs.org/repos/usb/basedrv/branches/wim/usbresmgr
https://svn.netlabs.org/repos/usb/basedrv/branches/wim/usbcalls

Changeset [1220]: USBCALLS: fix UsbBulkRead for PtPro110.

For more information see my "USB Resource Manager" web page:

http://home.hccnet.nl/w.m.brul/usbcalls/index.html


Description
-----------

This (beta test) matched set of USBCALLS.DLL and USBRESMG.SYS supports a.o.
interrupt write and isochronous transfers.


Installation
------------
Move USBRES02.ZIP into a directory of your choice and unzip it.
In order to replace USBCALLS.DLL you may have to close the eCenter first.
Replace USBCALLS.DLL and USBCALLS.SYM in your \ECS\DLL or \OS2\DLL directory
and USBRESMG.SYS and USBRESMG.SYM in your \ECS\BOOT or \OS2\BOOT directory.
Restart your system.

