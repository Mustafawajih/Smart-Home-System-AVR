/*
 * EXT_int_Type.h
 *
 * Created: 10/6/2023 3:56:45 PM
 *  Author: Musta
 */ 


#ifndef EXT_INT_TYPE_H_
#define EXT_INT_TYPE_H_

typedef enum{
	
	Ext_INT0,
	Ext_INT1,
	Ext_INT2
	
}Ext_Int_Types;

typedef enum{
	
	Low_Level,
	Both_Edges,
	Falling_Edge,
	Rising_Edge
	
}Ext_Int_SnControl;

#endif /* EXT_INT_TYPE_H_ */