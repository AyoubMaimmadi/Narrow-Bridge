/* ---------------------------------------------------------------- */
/* MONITOR  bridge-m:                                               */
/*    This monitor solves the bridge-crossing problem.  It consists */
/* of the following procedures:                                     */
/*    (1) BridgeInit()     - initialize bridge                      */
/*    (2) ArriveBridge()   - called when a vehicle arrives at the   */
/*                           bridge                                 */
/*    (3) ExitBridge()     - called when a vehicle exits the bridge */
/* ---------------------------------------------------------------- */

#ifndef  _CK_bridge_m_h
#define  _CK_bridge_m_h

void  BridgeInit(void);
void  ArriveBridge(int Direction);
void  ExitBridge(int Direction);

#endif

