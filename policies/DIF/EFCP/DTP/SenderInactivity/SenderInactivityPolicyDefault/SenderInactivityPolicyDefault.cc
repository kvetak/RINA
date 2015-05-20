/*
 * SenderInactivityPolicyDefault.cc
 *
 *  Created on: May 3, 2015
 *      Author: badluck
 */

#include "SenderInactivityPolicyDefault.h"

Register_Class(SenderInactivityPolicyDefault);

SenderInactivityPolicyDefault::SenderInactivityPolicyDefault()
{


}

SenderInactivityPolicyDefault::~SenderInactivityPolicyDefault()
{

}

bool SenderInactivityPolicyDefault::run(DTPState* dtpState, DTCPState* dtcpState)
{
  defaultAction(dtpState, dtcpState);
  return false;
}
