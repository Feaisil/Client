#include "../pch.h"
#include "EmptyEvent.h"

//////////////////////////////////////////////////////////////////////////////////////////
EmptyEvent &EmptyEvent::GetInstance( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns a valid empty event.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    static EmptyEvent emptyEvent;

    return emptyEvent;
}