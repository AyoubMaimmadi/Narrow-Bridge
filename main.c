/* ---------------------------------------------------------------- */
/* MONITOR  bridge-m:                                               */
/*    This monitor solves the bridge-crossing problem.  It consists */
/* of the following procedures:                                     */
/*    (1) BridgeInit()     - initialize bridge                      */
/*    (2) ArriveBridge()   - called when a vehicle arrives at the   */
/*                           bridge                                 */
/*    (3) ExitBridge()     - called when a vehicle exits the bridge */
/* ---------------------------------------------------------------- */

#include  <thread.h>

#include  "bridge-m.h"

#define   MAX_VEHICLE  3                /* max vehicle on bridge    */
#define   TRUE         1
#define   FALSE        0
#define   EAST         0                /* east bound               */
#define   WEST         1                /* west bound               */

static int  CurrentDirection;           /* current direction of cars*/
static int  VehicleCount;               /* # of vehicle on bridge   */
static int  Waiting[2];                 /* # east/west bound waiting*/

static mutex_t  MonitorLock;            /* monitor lock             */
static cond_t   EastWest[2];            /* blocking east/west cars  */

/* ---------------------------------------------------------------- */
/* FUNCTION  BridgeInit():                                          */
/*    This function initialize the bridge monitor.                  */
/* ---------------------------------------------------------------- */

void  BridgeInit(void)
{
     VehicleCount = 0;                  /* no vehicle on bridge     */
     Waiting[0] = Waiting[1] = 0;       /* no vehicle waiting       */

     mutex_init(&MonitorLock, USYNC_THREAD, (void *) NULL);
     cond_init(&(EastWest[0]), USYNC_THREAD, (void *) NULL);
     cond_init(&(EastWest[1]), USYNC_THREAD, (void *) NULL);
}

/* ---------------------------------------------------------------- */
/* FUNCTION  isSafe():                                              */
/*    This function tests if a vehicle can proceed.  Since it is a  */
/* static function, it can only be accessed with this file.         */
/* ---------------------------------------------------------------- */

static int  isSafe(int Direction)
{
     if (VehicleCount == 0)             /* if no vehicle on bridge  */
          return  TRUE;                 /* safe to cross            */
     else if ((VehicleCount < MAX_VEHICLE) && (CurrentDirection == Direction))
          return  TRUE;                 /* if < 3 in same direction */
     else
          return  FALSE;                /* otherwise, do not procee */
}

/* ---------------------------------------------------------------- */
/* FUNCTION  ArriveBridge():                                        */
/*    This function is called when a vehicle arrives at the bridge  */
/* ---------------------------------------------------------------- */

void  ArriveBridge(int Direction)
{
     mutex_lock(&MonitorLock);        /* lock the monitor         */
          if (!isSafe(Direction)) {
               Waiting[Direction]++;    /* no, wait at the bridge   */
               while (!isSafe(Direction))    /* safe to cross?      */
                    cond_wait(&(EastWest[Direction]), &MonitorLock);
               Waiting[Direction]--;    /* go back to test again    */
          }
          VehicleCount++;               /* can proceed              */
          CurrentDirection = Direction; /* set direction            */
     mutex_unlock(&MonitorLock);      /* release monitor          */
}

/* ---------------------------------------------------------------- */
/* FUNCTION  ExitBridge():                                          */
/*    This function is called when a vehicle exits the bridge.      */
/* ---------------------------------------------------------------- */

void  ExitBridge(int Direction)
{
     mutex_lock(&MonitorLock);        /* lock the monitor         */
          VehicleCount--;               /* one vehicle exits        */
          if (VehicleCount > 0)         /* have vehicles on bridge? */
               cond_signal(&(EastWest[Direction]));/* yes,same dir*/
          else {                        /* bridge is empty          */
               if (Waiting[1-Direction] != 0)  /* any opposite wait?*/
                    cond_signal(&(EastWest[1-Direction])); /* yes */
               else                     /* no, release the same dir */
                    cond_signal(&(EastWest[Direction]));
          }
     mutex_unlock(&MonitorLock);      /* release the monitor      */
}


