/*
 * GINT.c
 *
 * Created: 10/6/2023 3:50:14 PM
 *  Author: Musta
 */ 

#include "GNIT.h"

void EnableAllInterrupts()
{
	SET_BIT(GINT_SREG_Reg, GINT_SREG_IBit);
}
//-----------------------------------------------------
void DisableAllInterrupts()
{
	CLR_BIT(GINT_SREG_Reg, GINT_SREG_IBit);
}