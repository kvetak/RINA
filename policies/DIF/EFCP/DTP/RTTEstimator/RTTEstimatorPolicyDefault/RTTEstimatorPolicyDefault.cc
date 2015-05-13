/*
 * RTTEstimatorPolicyDefault.c
 *
 *  Created on: May 3, 2015
 *      Author: badluck
 */

#include "RTTEstimatorPolicyDefault.h"
#include "ControlPDU_m.h"

Register_Class(RTTEstimatorPolicyDefault);

RTTEstimatorPolicyDefault::RTTEstimatorPolicyDefault()
{
  // TODO Auto-generated constructor stub

}

RTTEstimatorPolicyDefault::~RTTEstimatorPolicyDefault()
{
  // TODO Auto-generated destructor stub
}

bool RTTEstimatorPolicyDefault::run(DTPState* dtpState, DTCPState* dtcpState)
{
  defaultAction(dtpState, dtcpState);
  return true;
}
