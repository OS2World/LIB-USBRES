#define INCL_DOSERRORS
#define INCL_DOSSEMAPHORES
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#include <OS2.h>

#ifndef ERROR_USER_DEFINED_BASE
#define ERROR_USER_DEFINED_BASE         0xFF00

#define ERROR_I24_WRITE_PROTECT         0
#define ERROR_I24_BAD_UNIT              1
#define ERROR_I24_NOT_READY             2
#define ERROR_I24_BAD_COMMAND           3
#define ERROR_I24_CRC                   4
#define ERROR_I24_BAD_LENGTH            5
#define ERROR_I24_SEEK                  6
#define ERROR_I24_NOT_DOS_DISK          7
#define ERROR_I24_SECTOR_NOT_FOUND      8
#define ERROR_I24_OUT_OF_PAPER          9
#define ERROR_I24_WRITE_FAULT           10
#define ERROR_I24_READ_FAULT            11
#define ERROR_I24_GEN_FAILURE           12
#define ERROR_I24_DISK_CHANGE           13
#define ERROR_I24_WRONG_DISK            15
#define ERROR_I24_UNCERTAIN_MEDIA       16
#define ERROR_I24_CHAR_CALL_INTERRUPTED 17
#define ERROR_I24_NO_MONITOR_SUPPORT    18
#define ERROR_I24_INVALID_PARAMETER     19
#define ERROR_I24_DEVICE_IN_USE         20
#define ERROR_I24_QUIET_INIT_FAIL       21
#endif

#include "usbcalls.h"

#define  IOCAT_USBRES            0xA0  // USB Resource Manager
#define  IOCTLF_GET_NUMDEVICES   0x31  // GetNumberDevices
#define  IOCTLF_GET_DEVICEREPORT 0x32  // GetDeviceReport
#define  IOCTLF_ACQUIRE_DEVICE   0x33  // AcquireDevice
#define  IOCTLF_RELEASE_DEVICE   0x34  // ReleaseDevice
#define  IOCTLF_GET_STRINGREPORT 0x35  // GetStringReport
#define  IOCTLF_SEND_CTRLURB     0x36  // SendCtrlURB
#define  IOCTLF_SEND_DATAURB     0x37  // SendDataURB
#define  IOCTLF_GET_DEVICEINFO   0x39  // GetDeviceInfo
#define  IOCTLF_ISO_OPEN         0x3A  // IsoOpen
#define  IOCTLF_SEND_ISOURB      0x3B  // SendIsoURB
#define  IOCTLF_ISO_CLOSE        0x3C  // IsoClose
#define  IOCTLF_CANCEL_IORB      0x3D  // CancelIoRB
#define  IOCTLF_FIXUP_DEVICE     0x40  // FixupDevice
#define  IOCTLF_REG_STATUSSEM    0x41  // RegisterStatusSemaphore
#define  IOCTLF_DEREG_STATUSSEM  0x42  // DeregisterStatusSemaphore
#define  IOCTLF_REG_DEVICESEM    0x43  // RegisterDeviceSemaphore
#define  IOCTLF_DEREG_DEVICESEM  0x44  // DeregisterDeviceSemaphore

#define NOTIFY_FREE   0
#define NOTIFY_CHANGE 1
#define NOTIFY_DEVICE 2
#define MAX_NOTIFICATIONS 256

typedef struct
{
  HEV    hDeviceAdded;
  HEV    hDeviceRemoved;
  USHORT usFlags;
  USHORT usVendor;
  USHORT usProduct;
  USHORT usBCDDevice;
} NOTIFYENTRY, *PNOTIFYENTRY;

#define DEV_SEM_ADD       0x00000001
#define DEV_SEM_REMOVE    0x00000002
#define DEV_SEM_MASK      0x00000003
#define DEV_SEM_VENDORID  0x00000004
#define DEV_SEM_PRODUCTID 0x00000008
#define DEV_SEM_BCDDEVICE 0x00000010

typedef struct{
  ULONG  ulSize;
  ULONG  ulCaps;
  ULONG  ulSemDeviceAdd;
  ULONG  ulSemDeviceRemove;
} STATUSEVENTSET, *PSTATUSEVENTSET;

typedef struct{
  ULONG  ulSize;
  ULONG  ulCaps;
  ULONG  ulSemDeviceAdd;
  ULONG  ulSemDeviceRemove;
  USHORT usVendorID;
  USHORT usProductID;
  USHORT usBCDDevice;
  USHORT usStatus;
} DEVEVENTSET, *PDEVEVENTSET;

typedef struct
{
  ULONG  ulDevHandle;
  ULONG  ulInfoLength;
} DEVGETINFO, *PDEVGETINFO;

typedef struct
{
  ULONG  ulDevHandle;
  USHORT usLangID;
  UCHAR  ucStringID;
  UCHAR  ucReserved;
} DEVGETSTRING, *PDEVGETSTRING;

typedef struct
{
  USHORT usVendorID;
  USHORT usProductID;
  USHORT usBCDDevice;
  USHORT usDeviceNumber; // Get the usDeviceNumber device.
                         // 0 means 1st not aquired device.
                         // 2 means aquire the 2nd device.
} ACQUIREDEV, *PACQUIREDEV;

typedef struct
{
  // request header
  ULONG  ulDevHandle;
  UCHAR  ucEndpoint;
  UCHAR  ucAltInterface;
  ULONG  ulEvent;
  USHORT usStatus;
} USBCALLS_CANCEL_REQ, *PUSBCALLS_CANCEL_REQ;

typedef struct
{
  // request header
  ULONG  ulDevHandle;
  UCHAR  ucEndpoint;
  UCHAR  ucAltInterface;
  ULONG  ulEventDone;
  ULONG  ulParmAddress;
  USHORT usParmLength;
  ULONG  ulDataAddress;
  USHORT usDataLength;
} USBCALLS_REQ, *PUSBCALLS_REQ;

typedef struct
{
  // request header
  USBCALLS_REQ hdr;
  // request specific
  UCHAR  bmRequestType;
  UCHAR  bRequest;
  USHORT wValue;
  USHORT wIndex;
} USBCALLS_CTRL_REQ, *PUSBCALLS_CTRL_REQ;

typedef struct
{
  // request header
  USBCALLS_REQ hdr;
  // request specific
  USHORT usFlags;
} USBCALLS_DATA_REQ, *PUSBCALLS_DATA_REQ;

typedef struct
{
  // request header
  USBCALLS_REQ hdr;
  // request specific
  USHORT usFrameLength;
  USHORT usFrameCount;
} USBCALLS_ISO_REQ, *PUSBCALLS_ISO_REQ;

typedef struct
{
  ULONG  ulDevHandle;
  UCHAR  ucEndpoint;
  UCHAR  ucAltInterface;
  USHORT usStatus;
  USHORT usBufferCount;
  USHORT usFrameLength;
} USBCALLS_ISO_OPEN, *PUSBCALLS_ISO_OPEN;

typedef struct
{
  ULONG  ulDevHandle;
  UCHAR  ucEndpoint;
  UCHAR  ucAltInterface;
  USHORT usStatus;
} USBCALLS_ISO_CLOSE, *PUSBCALLS_ISO_CLOSE;

typedef struct
{
  ULONG  ulDevHandle;
  UCHAR  ucConfiguration;
  USHORT usStatus;
} LIBUSB_FIXUP, *PLIBUSB_FIXUP;

/******************************************************************************/

HFILE g_hUSBDrv;
BOOL  g_fInit;
ULONG g_ulFreeNotifys;
HMTX  g_hSemNotifytable;
NOTIFYENTRY g_Notifications[MAX_NOTIFICATIONS];

void InitUsbCalls()
{
  ULONG i;
  ULONG ulAction;
  APIRET rc;

  rc = DosOpen( "USBRESM$",
                &g_hUSBDrv,
                &ulAction,
                0,
                FILE_NORMAL,
                OPEN_ACTION_OPEN_IF_EXISTS,
                OPEN_ACCESS_READWRITE |
                OPEN_FLAGS_NOINHERIT |
                OPEN_SHARE_DENYNONE,
                0 );
  if(rc)
  {
    g_hUSBDrv = 0;
    g_fInit   = FALSE;

  }
  else
  {
    // @@ToDO Add EnvVar or INI for dynamically setting the number
    for(i=0;i<MAX_NOTIFICATIONS;i++)
    {
      g_Notifications[i].usFlags        = NOTIFY_FREE;
      g_Notifications[i].hDeviceAdded   = 0;
      g_Notifications[i].hDeviceRemoved = 0;
      g_Notifications[i].usVendor       = 0;
      g_Notifications[i].usProduct      = 0;
      g_Notifications[i].usBCDDevice    = 0;
    }
    rc=DosCreateMutexSem(NULL,&g_hSemNotifytable,DC_SEM_SHARED,FALSE);
    if(rc)
    {
      DosClose(g_hUSBDrv);
      g_hUSBDrv = 0;
      g_fInit   = FALSE;
    }
    else g_fInit = TRUE;
  }
}

BOOL IsBadReadPointer(PVOID pBase, ULONG ulSize)
{
  APIRET rc;
  ULONG ulFlags;

  rc = DosQueryMem(pBase, &ulSize, &ulFlags);

  return rc!=0?TRUE:(ulFlags&PAG_READ)&&(ulFlags&PAG_COMMIT)?FALSE:TRUE;
}

BOOL IsBadWritePointer(PVOID pBase, ULONG ulSize)
{
  APIRET rc;
  ULONG ulFlags;

  rc = DosQueryMem(pBase, &ulSize, &ulFlags);

  return rc!=0?TRUE:((ulFlags&PAG_WRITE)==PAG_WRITE&&(ulFlags&PAG_COMMIT)==PAG_COMMIT)?FALSE:TRUE;
}

APIRET APIENTRY UsbQueryNumberDevices( ULONG *pulNumDev)
{
  APIRET rc;
  ULONG ulLength;

  if (!g_fInit) return USB_NOT_INIT;

  if (IsBadWritePointer(pulNumDev,sizeof(ULONG)))
    return ERROR_INVALID_PARAMETER;

  *pulNumDev = 0;

  ulLength = sizeof(ULONG);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_GET_NUMDEVICES,
                    NULL,0,NULL,pulNumDev,ulLength,&ulLength);
  return rc;
}

APIRET APIENTRY UsbQueryDeviceInfo (ULONG ulDevNumber,
                                    ULONG *pulBufLen,
                                    UCHAR *pucData)
{
  APIRET rc;
  ULONG ulParmLen;

  if (!g_fInit) return USB_NOT_INIT;

  if (IsBadWritePointer(pulBufLen,sizeof(ULONG)))
    return ERROR_INVALID_PARAMETER;

  if (IsBadWritePointer(pucData,*pulBufLen))
    return ERROR_INVALID_PARAMETER;

  ulParmLen = sizeof(ulDevNumber);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_GET_DEVICEINFO,
                    (PVOID)&ulDevNumber,ulParmLen,&ulParmLen,
                    pucData,*pulBufLen,pulBufLen);

  return rc;
}

APIRET APIENTRY UsbQueryDeviceReport (ULONG ulDevNumber,
                                      ULONG *pulBufLen,
                                      UCHAR *pucData)
{
  APIRET rc;
  DEVGETINFO Parm;
  ULONG ulParmLen;

  if (!g_fInit) return USB_NOT_INIT;

  if (IsBadWritePointer(pulBufLen,sizeof(ULONG)))
    return ERROR_INVALID_PARAMETER;

  if (pucData!=NULL && IsBadWritePointer(pucData,*pulBufLen))
    return ERROR_INVALID_PARAMETER;

  if (pucData==NULL) *pulBufLen = 0;

  Parm.ulDevHandle = ulDevNumber;
  Parm.ulInfoLength = *pulBufLen;

  ulParmLen = sizeof(DEVGETINFO);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_GET_DEVICEREPORT,
                    &Parm,ulParmLen,&ulParmLen,
                    pucData,*pulBufLen,pulBufLen);

  *pulBufLen = Parm.ulInfoLength;

  return rc;
}

APIRET APIENTRY UsbQueryStringReport (ULONG ulDevNumber,
                                      USHORT usLangID,
                                      UCHAR ucStringID,
                                      ULONG *pulBufLen,
                                      UCHAR *pucData)
{
  APIRET rc;
  DEVGETSTRING Parm;
  ULONG ulParmLen, ulDataLen;

  if (!g_fInit) return USB_NOT_INIT;

  // verify string transfer length pointer
  if (IsBadWritePointer(pulBufLen,sizeof(ULONG)))
    return ERROR_INVALID_PARAMETER;

  // verify string transfer length value
  if ((*pulBufLen<0x0100)||(*pulBufLen>0x8000))
    return ERROR_INVALID_PARAMETER;

  // verify string transfer buffer pointer
  if (IsBadWritePointer(pucData,*pulBufLen))
    return ERROR_INVALID_PARAMETER;

  Parm.ulDevHandle = ulDevNumber;
  Parm.usLangID = usLangID;
  Parm.ucStringID = ucStringID;
  Parm.ucReserved = 0;

  ulParmLen = sizeof(DEVGETSTRING);
  ulDataLen = *pulBufLen;

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_GET_STRINGREPORT,
                    &Parm,ulParmLen,&ulParmLen,
                    pucData,ulDataLen,&ulDataLen);

  *pulBufLen = *pucData;

  return rc;
}

APIRET APIENTRY UsbRegisterChangeNotification( PUSBNOTIFY pNotifyID,
                                      HEV hDeviceAdded,
                                      HEV hDeviceRemoved)
{
  APIRET rc;
  int i;
  STATUSEVENTSET EventSet;
  ULONG ulSize;

  if(!g_fInit)
    return USB_NOT_INIT;

  if( IsBadWritePointer(pNotifyID, sizeof(ULONG)) ||
      (hDeviceAdded==0 && hDeviceRemoved==0) )
    return ERROR_INVALID_PARAMETER;

  ulSize = sizeof(EventSet);
  EventSet.ulSize = ulSize;

  if(hDeviceAdded!=0)
  {
    ULONG ulCnt;
    rc = DosQueryEventSem(hDeviceAdded,&ulCnt);
    if(rc)
      return rc;
    EventSet.ulCaps         = DEV_SEM_ADD;
    EventSet.ulSemDeviceAdd = hDeviceAdded;
  }

  if(hDeviceRemoved!=0)
  {
    ULONG ulCnt;
    rc = DosQueryEventSem(hDeviceRemoved,&ulCnt);
    if(rc)
      return rc;
    EventSet.ulCaps            |= DEV_SEM_REMOVE;
    EventSet.ulSemDeviceRemove = hDeviceRemoved;
  }

  rc = DosRequestMutexSem(g_hSemNotifytable,SEM_INDEFINITE_WAIT);
  if(rc)
    return rc;

  for(i=0;i<MAX_NOTIFICATIONS;i++)
  {
    if( g_Notifications[i].usFlags == NOTIFY_FREE)
    {
      g_Notifications[i].usFlags = NOTIFY_CHANGE;
      g_Notifications[i].hDeviceAdded   = hDeviceAdded;
      g_Notifications[i].hDeviceRemoved = hDeviceRemoved;
      g_Notifications[i].usVendor       = 0;
      g_Notifications[i].usProduct      = 0;
      g_Notifications[i].usBCDDevice    = 0;
      break;
    }
  }
  DosReleaseMutexSem(g_hSemNotifytable);
  if(i==MAX_NOTIFICATIONS)
    return USB_ERROR_NO_MORE_NOTIFICATIONS;

  // @@ToDo come up with a better way to generate IDs
  *pNotifyID = (USBNOTIFY) (&g_Notifications[i]);
  rc = DosDevIOCtl( g_hUSBDrv,
                    IOCAT_USBRES, IOCTLF_REG_STATUSSEM,
                    NULL, 0, NULL,
                    &EventSet,ulSize, &ulSize);
  if(rc)
  {
    g_Notifications[i].usFlags = NOTIFY_FREE;
    *pNotifyID = 0;
  }
  return rc;
}

APIRET APIENTRY UsbRegisterDeviceNotification( PUSBNOTIFY pNotifyID,
                                      HEV hDeviceAdded,
                                      HEV hDeviceRemoved,
                                      USHORT usVendor,
                                      USHORT usProduct,
                                      USHORT usBCDVersion)
{
  DEVEVENTSET EventSet;
  ULONG ulCnt,ulSize;
  int i;
  APIRET rc;

  if(!g_fInit)
    return USB_NOT_INIT;

  if( IsBadWritePointer(pNotifyID, sizeof(ULONG)) ||
      hDeviceAdded==0 || hDeviceRemoved==0 ||
      usVendor  == 0  || usVendor  == 0xFFFF ||
      usProduct == 0  || usProduct == 0xFFFF )
    return ERROR_INVALID_PARAMETER;


  rc = DosQueryEventSem(hDeviceAdded,&ulCnt);
  if(rc)
    return rc;
  rc = DosQueryEventSem(hDeviceRemoved,&ulCnt);
  if(rc)
    return rc;

  ulSize = sizeof(EventSet);
  EventSet.ulSize            = ulSize;
  EventSet.ulCaps            = DEV_SEM_ADD | DEV_SEM_REMOVE |
                               DEV_SEM_VENDORID | DEV_SEM_PRODUCTID |
                               DEV_SEM_BCDDEVICE ;
  EventSet.ulSemDeviceAdd    = hDeviceAdded;
  EventSet.ulSemDeviceRemove = hDeviceRemoved;
  EventSet.usVendorID        = usVendor;
  EventSet.usProductID       = usProduct;
  EventSet.usBCDDevice       = usBCDVersion;
  EventSet.usStatus          = 0;

  rc = DosRequestMutexSem(g_hSemNotifytable,SEM_INDEFINITE_WAIT);

  if(rc)
    return rc;

  for(i=0;i<MAX_NOTIFICATIONS;i++)
  {
    if( g_Notifications[i].usFlags == NOTIFY_FREE)
    {
      g_Notifications[i].usFlags = NOTIFY_DEVICE;
      g_Notifications[i].hDeviceAdded   = hDeviceAdded;
      g_Notifications[i].hDeviceRemoved = hDeviceRemoved;
      g_Notifications[i].usVendor       = usVendor;
      g_Notifications[i].usProduct      = usProduct;
      g_Notifications[i].usBCDDevice    = usBCDVersion;
      break;
    }
  }
  DosReleaseMutexSem(g_hSemNotifytable);
  if(i==MAX_NOTIFICATIONS)
    return USB_ERROR_NO_MORE_NOTIFICATIONS;

  // @@ToDo come up with a better way to generate IDs
  *pNotifyID = (USBNOTIFY) (&g_Notifications[i]);
  rc = DosDevIOCtl( g_hUSBDrv,
                    IOCAT_USBRES, IOCTLF_REG_DEVICESEM,
                    NULL, 0, NULL,
                    &EventSet,ulSize, &ulSize);
  if(rc)
  {
    if( rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER) )
      rc= ERROR_INVALID_PARAMETER;
    if( rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_GEN_FAILURE) )
      rc= EventSet.usStatus;

    g_Notifications[i].usFlags = NOTIFY_FREE;
    *pNotifyID = 0;
  }
  return rc;
}

APIRET APIENTRY UsbDeregisterNotification( USBNOTIFY NotifyID )
{
  DEVEVENTSET EventSet;
  USBNOTIFY   MinID,MaxID;
  ULONG       Index, ulFunction, ulSize;
  APIRET      rc;

  if(!g_fInit)
    return USB_NOT_INIT;

  MinID = (USBNOTIFY) (&g_Notifications[0]);
  MaxID = (USBNOTIFY) (&g_Notifications[MAX_NOTIFICATIONS-1]);

  if(NotifyID<MinID || NotifyID>MaxID)
    return ERROR_INVALID_PARAMETER;

  Index = NotifyID - MinID;

  if(Index % sizeof(NOTIFYENTRY))
    return ERROR_INVALID_PARAMETER;

  Index /= sizeof(NOTIFYENTRY);

  rc = DosRequestMutexSem(g_hSemNotifytable,SEM_INDEFINITE_WAIT);

  switch(g_Notifications[Index].usFlags)
  {
    case NOTIFY_FREE:
      DosReleaseMutexSem(g_hSemNotifytable);
      return ERROR_INVALID_PARAMETER;
    case NOTIFY_CHANGE:
      ulFunction  = IOCTLF_DEREG_STATUSSEM;
      ulSize = sizeof(STATUSEVENTSET);
      EventSet.ulSize            = ulSize;
      EventSet.ulCaps            = DEV_SEM_ADD | DEV_SEM_REMOVE;
      EventSet.ulSemDeviceAdd    = g_Notifications[Index].hDeviceAdded;
      EventSet.ulSemDeviceRemove = g_Notifications[Index].hDeviceRemoved;
      break;
    case NOTIFY_DEVICE:
      ulFunction = IOCTLF_DEREG_DEVICESEM;
      ulSize = sizeof(DEVEVENTSET);
      EventSet.ulSize            = ulSize;
      EventSet.ulCaps            = DEV_SEM_ADD | DEV_SEM_REMOVE |
                                   DEV_SEM_VENDORID | DEV_SEM_PRODUCTID |
                                   DEV_SEM_BCDDEVICE ;
      EventSet.ulSemDeviceAdd    = g_Notifications[Index].hDeviceAdded;
      EventSet.ulSemDeviceRemove = g_Notifications[Index].hDeviceRemoved;
      EventSet.usVendorID        = g_Notifications[Index].usVendor;
      EventSet.usProductID       = g_Notifications[Index].usProduct;
      EventSet.usBCDDevice       = g_Notifications[Index].usBCDDevice;
      EventSet.usStatus          = 0;
      break;
    default:
      DosReleaseMutexSem(g_hSemNotifytable);
      return ERROR_GEN_FAILURE;
  }

  rc = DosDevIOCtl( g_hUSBDrv,
                    IOCAT_USBRES, ulFunction,
                    NULL, 0, NULL,
                    &EventSet,ulSize, &ulSize);
  if(0==rc)
  {
    g_Notifications[Index].usFlags        = NOTIFY_FREE;
    g_Notifications[Index].hDeviceAdded   = 0;
    g_Notifications[Index].hDeviceRemoved = 0;
    g_Notifications[Index].usVendor       = 0;
    g_Notifications[Index].usProduct      = 0;
    g_Notifications[Index].usBCDDevice    = 0;
  } else
  {
    if( rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER) )
      rc= ERROR_INVALID_PARAMETER;
    if( rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_GEN_FAILURE) )
      rc= EventSet.usStatus;
  }
  DosReleaseMutexSem(g_hSemNotifytable);

  return rc;
}

APIRET APIENTRY UsbOpen( PUSBHANDLE pHandle,
                USHORT usVendor,
                USHORT usProduct,
                USHORT usBCDDevice,
                USHORT usEnumDevice)
{
  ULONG      ulParmLen, ulDataLen;
  ACQUIREDEV Acquire;
  APIRET     rc;

  if (!g_fInit) return USB_NOT_INIT;

  if (IsBadWritePointer(pHandle,sizeof(USBHANDLE)))
    return ERROR_INVALID_PARAMETER;

  Acquire.usVendorID     = usVendor;
  Acquire.usProductID    = usProduct;
  Acquire.usBCDDevice    = usBCDDevice;
  Acquire.usDeviceNumber = usEnumDevice;
  ulParmLen = sizeof(Acquire);
  ulDataLen = sizeof(USBHANDLE);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_ACQUIRE_DEVICE,
                    &Acquire,ulParmLen,&ulParmLen,
                    pHandle,ulDataLen,&ulDataLen);

  return rc;
}

APIRET APIENTRY UsbClose( USBHANDLE Handle)
{
  APIRET rc;
  ULONG ulDataLen,ulParmLen;
  if(!g_fInit)
    return USB_NOT_INIT;

  ulParmLen = sizeof(USBHANDLE);
  ulDataLen = 0;

  rc = DosDevIOCtl( g_hUSBDrv,
                    IOCAT_USBRES, IOCTLF_RELEASE_DEVICE,
                    (PVOID)&Handle, ulParmLen, &ulParmLen,
                    NULL, ulDataLen, &ulDataLen);
  return rc;
}

APIRET APIENTRY UsbCtrlMessage( USBHANDLE Handle,
                                UCHAR ucRequestType,
                                UCHAR ucRequest,
                                USHORT usValue,
                                USHORT usIndex,
                                USHORT usLength,
                                UCHAR *pucData,
                                ULONG ulTimeout)
{
  return UsbCtrlTransfer (Handle,0,0,ucRequestType,ucRequest,usValue,
                          usIndex,&usLength,pucData,ulTimeout);
}

APIRET APIENTRY UsbCtrlTransfer( USBHANDLE Handle,
                                 UCHAR Endpoint,
                                 UCHAR AltInterface,
                                 UCHAR ucRequestType,
                                 UCHAR ucRequest,
                                 USHORT usValue,
                                 USHORT usIndex,
                                 USHORT *pusLength,
                                 UCHAR *pucData,
                                 ULONG ulTimeout)
{
  APIRET rc;
  ULONG  ulEventDone;
  USBCALLS_CTRL_RSP CtrlResponse;

  if (!g_fInit) return USB_NOT_INIT;

  // verify control transfer length pointer
  if (IsBadWritePointer(pusLength,sizeof(ULONG)))
    return ERROR_INVALID_PARAMETER;

  // verify control transfer maximum length value
  if (*pusLength>0x8000) return ERROR_INVALID_PARAMETER;

  if (*pusLength) // control transfer with data stage
  {
    if ((ucRequestType&0x80)==0x00) // host-to-device
    {
      // verify host-to-device buffer pointer
      if (IsBadReadPointer(pucData,*pusLength))
        return ERROR_INVALID_PARAMETER;
    }
    else // device-to-host
    {
      // verify device-to-host buffer pointer
      if (IsBadWritePointer(pucData,*pusLength))
        return ERROR_INVALID_PARAMETER;
    }
  }

  rc = DosCreateEventSem (NULL,(PHEV)&ulEventDone,DC_SEM_SHARED,FALSE);
  if (rc) return rc;

  CtrlResponse.usDataLength = *pusLength;
  rc = UsbStartCtrlTransfer (Handle,Endpoint,AltInterface,
                             ucRequestType,ucRequest,usValue,usIndex,
                             (PUCHAR)&CtrlResponse,pucData,ulEventDone);
  if (rc == NO_ERROR)
  {
    rc = DosWaitEventSem ((HEV)ulEventDone,(ulTimeout?ulTimeout:-1));
    if (rc != NO_ERROR)
      UsbCancelTransfer (Handle,Endpoint,AltInterface,ulEventDone);
    else rc = CtrlResponse.usStatus;
  }

  DosCloseEventSem ((HEV)ulEventDone);

  *pusLength = CtrlResponse.usDataLength;

  return rc;
}

APIRET APIENTRY UsbBulkRead (USBHANDLE Handle,
                             UCHAR Endpoint,
                             UCHAR AltInterface,
                             ULONG *pulNumBytes,
                             UCHAR *pucData,
                             ULONG ulTimeout)
{
  return UsbDataTransfer (Handle,Endpoint,AltInterface,pulNumBytes,pucData,
                          ulTimeout,USB_TRANSFER_FULL_SIZE);
}

APIRET APIENTRY UsbBulkWrite (USBHANDLE Handle,
                              UCHAR Endpoint,
                              UCHAR AltInterface,
                              ULONG ulNumBytes,
                              UCHAR *pucData,
                              ULONG ulTimeout)
{
  return UsbDataTransfer (Handle,Endpoint,AltInterface,&ulNumBytes,pucData,
                          ulTimeout,USB_TRANSFER_FULL_SIZE);
}

APIRET APIENTRY UsbDataTransfer (USBHANDLE Handle,
                                 UCHAR Endpoint,
                                 UCHAR AltInterface,
                                 ULONG *pulNumBytes,
                                 UCHAR *pucData,
                                 ULONG ulTimeout,
                                 USHORT usFlags)
{
  APIRET rc;
  ULONG ulDataLen, ulProcessed, ulToProcess;
  ULONG ulEventDone, ulTempEventCount;
  USBCALLS_DATA_RSP DataResponse;

  if (!g_fInit) return USB_NOT_INIT;

  // verify data transfer length pointer
  if (IsBadWritePointer(pulNumBytes,sizeof(ULONG)))
    return ERROR_INVALID_PARAMETER;

  if ((Endpoint&0x80)==0x00) // host-to-device
  {
    // verify host-to-device endpoint number
    if ((Endpoint<0x01)||(Endpoint>0x0F))
      return USB_ERROR_INVALID_ENDPOINT;

    if (*pulNumBytes==0) return 0;

    // verify host-to-device buffer pointer
    if (IsBadReadPointer(pucData,*pulNumBytes))
      return ERROR_INVALID_PARAMETER;
  }
  else // device to host
  {
    // verify device-to-host endpoint number
    if ((Endpoint<0x80)||(Endpoint>0x8F))
      return USB_ERROR_INVALID_ENDPOINT;

    if (*pulNumBytes==0) return 0;

    // verify device-to-host buffer pointer
    if (IsBadWritePointer(pucData,*pulNumBytes))
      return ERROR_INVALID_PARAMETER;
  }

  rc = DosCreateEventSem (NULL,(PHEV)&ulEventDone,DC_SEM_SHARED,FALSE);
  if (rc) return rc;

  ulToProcess = *pulNumBytes;
  ulProcessed = 0;

  do
  {
    // submit up to 32768 bytes data transfer request
    ulDataLen = (ulToProcess<0x8000)?ulToProcess:0x8000;

    DataResponse.usDataLength = (USHORT)ulDataLen;
    rc = UsbStartDataTransfer (Handle,Endpoint,AltInterface,
                               (PUCHAR)&DataResponse,pucData,
                               ulEventDone,usFlags);
    if (rc == NO_ERROR)
    {
      rc = DosWaitEventSem ((HEV)ulEventDone,(ulTimeout?ulTimeout:-1));
      if (rc != NO_ERROR)
        UsbCancelTransfer (Handle,Endpoint,AltInterface,ulEventDone);
      else rc = DataResponse.usStatus;
    }
    if (rc != NO_ERROR) break;

    ulProcessed += DataResponse.usDataLength;
    if (DataResponse.usDataLength != (USHORT)ulDataLen)
    {
      if (usFlags == USB_TRANSFER_FULL_SIZE)
        rc = USB_ERROR_LESSTRANSFERED;
      break;
    }

    // adjust count and pointer
    ulToProcess -= DataResponse.usDataLength;
    pucData += DataResponse.usDataLength;

    DosResetEventSem ((HEV)ulEventDone,&ulTempEventCount);

  } while (ulToProcess > 0);

  DosCloseEventSem ((HEV)ulEventDone);

  *pulNumBytes = ulProcessed;

  return rc;
}

APIRET APIENTRY UsbIrqRead (USBHANDLE Handle,
                            UCHAR Endpoint,
                            UCHAR AltInterface,
                            ULONG *pulNumBytes,
                            UCHAR *pucData,
                            ULONG ulTimeout)
{
  return UsbDataTransfer (Handle,Endpoint,AltInterface,pulNumBytes,pucData,
                          ulTimeout,0);
}

APIRET APIENTRY UsbIrqWrite (USBHANDLE Handle,
                             UCHAR Endpoint,
                             UCHAR AltInterface,
                             ULONG ulNumBytes,
                             UCHAR *pucData,
                             ULONG ulTimeout)
{
  return UsbDataTransfer (Handle,Endpoint,AltInterface,&ulNumBytes,pucData,
                          ulTimeout,0);
}

APIRET APIENTRY UsbIsoOpen (USBHANDLE Handle,
                            UCHAR  Endpoint,
                            UCHAR  AltInterface,
                            USHORT usBufferCount,
                            USHORT usFrameLength)
{
  USBCALLS_ISO_OPEN IsoOpenRequest;
  ULONG ulParmLen;
  APIRET rc;

  if (!g_fInit) return USB_NOT_INIT;

  IsoOpenRequest.ulDevHandle = Handle;
  IsoOpenRequest.ucEndpoint = Endpoint;
  IsoOpenRequest.ucAltInterface = AltInterface;
  IsoOpenRequest.usBufferCount = usBufferCount;
  IsoOpenRequest.usFrameLength = usFrameLength;

  ulParmLen = sizeof(USBCALLS_ISO_OPEN);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_ISO_OPEN,
                    (PVOID)&IsoOpenRequest,ulParmLen,&ulParmLen,
                    NULL,0,NULL);

  if (rc != NO_ERROR)
  {
    if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER))
      rc = ERROR_INVALID_PARAMETER;
    if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_GEN_FAILURE))
      rc = IsoOpenRequest.usStatus;
  }

  return rc;
}

APIRET APIENTRY UsbIsoClose (USBHANDLE Handle,
                             UCHAR  Endpoint,
                             UCHAR  AltInterface)
{
  USBCALLS_ISO_CLOSE IsoCloseRequest;
  ULONG ulParmLen;
  APIRET rc;

  if (!g_fInit) return USB_NOT_INIT;

  IsoCloseRequest.ulDevHandle = Handle;
  IsoCloseRequest.ucEndpoint = Endpoint;
  IsoCloseRequest.ucAltInterface = AltInterface;

  ulParmLen = sizeof(USBCALLS_ISO_CLOSE);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_ISO_CLOSE,
                    (PVOID)&IsoCloseRequest,ulParmLen,&ulParmLen,
                    NULL,0,NULL);

  if (rc != NO_ERROR)
  {
    if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER))
      rc = ERROR_INVALID_PARAMETER;
    if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_GEN_FAILURE))
      rc = IsoCloseRequest.usStatus;
  }

  return rc;
}

APIRET APIENTRY UsbStartCtrlTransfer (USBHANDLE Handle,
                                      UCHAR  Endpoint,
                                      UCHAR  AltInterface,
                                      UCHAR  ucRequestType,
                                      UCHAR  ucRequest,
                                      USHORT usValue,
                                      USHORT usIndex,
                                      UCHAR  *pucParm,
                                      UCHAR  *pucData,
                                      ULONG  ulEvent)
{
  APIRET             rc;
  ULONG              ulParmLen;
  PUSBCALLS_CTRL_RSP pCtrlResponse;
  USBCALLS_CTRL_REQ  CtrlRequest;

  if (!g_fInit) return USB_NOT_INIT;

  pCtrlResponse = (PUSBCALLS_CTRL_RSP)pucParm;
  pCtrlResponse->usStatus = USB_IORB_REQUEST;

  // check control transfer buffer length
  if (pCtrlResponse->usDataLength > 0x8000)
    return ERROR_INVALID_PARAMETER;

  CtrlRequest.hdr.ulDevHandle = Handle;
  CtrlRequest.hdr.ucEndpoint = Endpoint;
  CtrlRequest.hdr.ucAltInterface = AltInterface;
  CtrlRequest.hdr.ulEventDone = ulEvent;
  CtrlRequest.hdr.ulParmAddress = (ULONG)pucParm;
  CtrlRequest.hdr.usParmLength = sizeof(USBCALLS_CTRL_RSP);
  CtrlRequest.hdr.ulDataAddress = (ULONG)pucData;
  CtrlRequest.hdr.usDataLength = pCtrlResponse->usDataLength;
  CtrlRequest.bmRequestType = ucRequestType;
  CtrlRequest.bRequest = ucRequest;
  CtrlRequest.wValue = usValue;
  CtrlRequest.wIndex = usIndex;

  ulParmLen = sizeof(USBCALLS_CTRL_REQ);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_SEND_CTRLURB,
                    (PVOID)&CtrlRequest,ulParmLen,&ulParmLen,
                    NULL,0,NULL);

  if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER))
    rc = ERROR_INVALID_PARAMETER;

  return rc;
}

APIRET APIENTRY UsbStartDataTransfer (USBHANDLE Handle,
                                      UCHAR  Endpoint,
                                      UCHAR  AltInterface,
                                      UCHAR  *pucParm,
                                      UCHAR  *pucData,
                                      ULONG  ulEvent,
                                      USHORT usFlags)
{
  APIRET             rc;
  ULONG              ulParmLen;
  PUSBCALLS_DATA_RSP pDataResponse;
  USBCALLS_DATA_REQ  DataRequest;

  if (!g_fInit) return USB_NOT_INIT;

  pDataResponse = (PUSBCALLS_DATA_RSP)pucParm;
  pDataResponse->usStatus = USB_IORB_REQUEST;

  // check data transfer buffer length
  if (pDataResponse->usDataLength > 0x8000)
    return ERROR_INVALID_PARAMETER;

  DataRequest.hdr.ulDevHandle = Handle;
  DataRequest.hdr.ucEndpoint = Endpoint;
  DataRequest.hdr.ucAltInterface = AltInterface;
  DataRequest.hdr.ulEventDone = ulEvent;
  DataRequest.hdr.ulParmAddress = (ULONG)pucParm;
  DataRequest.hdr.usParmLength = sizeof(USBCALLS_DATA_RSP);
  DataRequest.hdr.ulDataAddress = (ULONG)pucData;
  DataRequest.hdr.usDataLength = pDataResponse->usDataLength;
  DataRequest.usFlags = usFlags;

  ulParmLen = sizeof(USBCALLS_DATA_REQ);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_SEND_DATAURB,
                    (PVOID)&DataRequest,ulParmLen,&ulParmLen,
                    NULL,0,NULL);

  if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER))
    rc = ERROR_INVALID_PARAMETER;

  return rc;
}

APIRET APIENTRY UsbStartIsoTransfer (USBHANDLE Handle,
                                     UCHAR  Endpoint,
                                     UCHAR  AltInterface,
                                     ULONG  ulEvent,
                                     UCHAR  *pucParm,
                                     UCHAR  *pucData,
                                     USHORT usFrameLength,
                                     USHORT usFrameCount)
{
  APIRET            rc;
  ULONG             ulParmLen;
  PUSBCALLS_ISO_RSP pIsoResponse;
  USBCALLS_ISO_REQ  IsoRequest;

  if (!g_fInit) return USB_NOT_INIT;

  pIsoResponse = (PUSBCALLS_ISO_RSP)pucParm;
  pIsoResponse->usStatus = USB_IORB_REQUEST;

  // check isochronous transfer buffer length
  if (pIsoResponse->usDataLength < usFrameCount*usFrameLength)
    return ERROR_INVALID_PARAMETER;

  IsoRequest.hdr.ulDevHandle = Handle;
  IsoRequest.hdr.ucEndpoint = Endpoint;
  IsoRequest.hdr.ucAltInterface = AltInterface;
  IsoRequest.hdr.ulEventDone = ulEvent;
  IsoRequest.hdr.ulParmAddress = (ULONG)pucParm;
  IsoRequest.hdr.usParmLength = (USHORT)(sizeof(USBCALLS_ISO_RSP)+usFrameCount*2);
  IsoRequest.hdr.ulDataAddress = (ULONG)pucData;
  IsoRequest.hdr.usDataLength = pIsoResponse->usDataLength;
  IsoRequest.usFrameLength = usFrameLength;
  IsoRequest.usFrameCount = usFrameCount;

  ulParmLen = sizeof(USBCALLS_ISO_REQ);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_SEND_ISOURB,
                    (PVOID)&IsoRequest,ulParmLen,&ulParmLen,
                    NULL,0,NULL);

  if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER))
    rc = ERROR_INVALID_PARAMETER;

  return rc;
}

APIRET APIENTRY UsbCancelTransfer (USBHANDLE Handle,
                                   UCHAR  Endpoint,
                                   UCHAR  AltInterface,
                                   ULONG  ulEvent)
{
  USBCALLS_CANCEL_REQ CancelRequest;
  ULONG ulParmLen;
  APIRET rc;

  if (!g_fInit) return USB_NOT_INIT;

  CancelRequest.ulDevHandle = Handle;
  CancelRequest.ucEndpoint = Endpoint;
  CancelRequest.ucAltInterface = AltInterface;
  CancelRequest.ulEvent = ulEvent;
  CancelRequest.usStatus = 0;

  ulParmLen = sizeof(USBCALLS_CANCEL_REQ);

  rc = DosDevIOCtl (g_hUSBDrv,IOCAT_USBRES,IOCTLF_CANCEL_IORB,
                    (PVOID)&CancelRequest,ulParmLen,&ulParmLen,
                    NULL,0,NULL);

  if (rc != NO_ERROR)
  {
    if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER))
      rc = ERROR_INVALID_PARAMETER;
    if (rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_GEN_FAILURE))
      rc = CancelRequest.usStatus;
  }

  return rc;
}

APIRET APIENTRY UsbFixupDevice( USBHANDLE Handle,
                                UCHAR ucConfiguration,
                                UCHAR *pucConfigurationData,
                                ULONG ulConfigurationLen )
{
  LIBUSB_FIXUP request;
  ULONG        ulParmLen;
  APIRET rc;

  request.ulDevHandle= Handle;
  request.ucConfiguration= ucConfiguration;
  request.usStatus= 0;
  ulParmLen= sizeof(LIBUSB_FIXUP);
  rc = DosDevIOCtl( g_hUSBDrv,
                    IOCAT_USBRES, IOCTLF_FIXUP_DEVICE,
                    (PVOID)&request, ulParmLen, &ulParmLen,
                    pucConfigurationData, ulConfigurationLen, &ulConfigurationLen);
  if( rc != NO_ERROR )
  {
    if( rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_INVALID_PARAMETER) )
      rc= ERROR_INVALID_PARAMETER;
    if( rc == (ERROR_USER_DEFINED_BASE|ERROR_I24_GEN_FAILURE) )
      rc= request.usStatus;
  }
  return rc;
}

 /*+-------------------------------------------------------------------+*/
 /*| _CRT_init is the C run-time environment initialization function.  |*/
 /*|It will return 0 to indicate success and -1 to indicate failure.   |*/
 /*+-------------------------------------------------------------------+*/

 /*+-------------------------------------------------------------------+*/
 /*| _CRT_term is the C run-time environment termination function.     |*/
 /*+-------------------------------------------------------------------+*/

#ifdef STATIC_LINK
int   _CRT_init (void);
void  _CRT_term(0UL);
#endif

/**
 * LibMain (_DLL_InitTerm) is the function that gets called by the operating
 * system loader when it loads and frees this DLL for each process
 * that accesses this DLL.  However, it only gets called the first
 * time the DLL is loaded and the last time it is freed for a
 * particular process.  The system linkage convention must be used
 * because the operating system loader is calling this function.
 */

APIRET APIENTRY LibMain (ULONG hModule, ULONG ulFlag)
{
  /* If flag is zero then the DLL is being loaded so initialization  */
  /* should be performed.  If flag is 1 then the DLL is being freed  */
  /* so termination should be performed.                             */

  switch (ulFlag)
  {
    case 0:
    /* The C run-time environment initialization function must
     * be called before any calls to C run-time functions that
     * are not inlined.
     */

#ifdef STATIC_LINK
      if (_CRT_init () == -1)
         return 0UL;
#endif
      InitUsbCalls();
      break;

    case 1:
      if(g_fInit)
      {
        int i;
        for(i=0;i<MAX_NOTIFICATIONS;i++)
        {
          if( g_Notifications[i].usFlags != NOTIFY_FREE)
          {
            // @@ ToDo deregister all Eventes in the driver on unload
          }
        }
        DosClose(g_hUSBDrv);
      }

#ifdef STATIC_LINK
      _CRT_term(0UL);
#endif
      break;

    default:
      return 0UL;
  }

  /* A nonzero value must be returned to indicate success. */
  return 1UL;
}

