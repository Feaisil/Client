#pragma warning( disable : 4786 )
#include "GameUI.h"

#include "../pch.h"

#include "RootBoxUI.h"
#include <algorithm>

// Chat box.
#include "ChatterUI.h"
// SideMenu box.
#include "SideMenu.h"
#include "..\SaveGame.h"
extern CSaveGame g_SaveGame;

using namespace std;

// Global variables
GameUI       *GameUI::draggedItem = NULL;
EventVisitor *GameUI::draggedEvent = NULL;
GameUI       *GameUI::draggedParentUI = NULL;
MousePos      GameUI::draggedInitialPos( 0, 0 );
bool          GameUI::leftMouseDown = false;

DWORD               GameUI::lastClickTime = 0xFFFFFFFF;
GameUI::MouseState  GameUI::currentMouseState = MouseNone;
GameUI       *GameUI::foregroundChild = NULL;

GameUI::GameUI() 
    : minimizedState( false ), 
      bDrawBlending(false),
      hiddenState( true ),
      framePos( 0, 0, 0, 0 ),
      helpText( NULL ),
      helpDisplayState( false ),
      helpDisplayX( 0 ),
      helpDisplayY( 0 ),
      lastClickedItem( NULL )
{
    hideEvent.SetUI( this );
    minimizeEvent.SetUI( this );
}

GameUI::~GameUI(){
    // If a font object is still attached.
    if( helpText != NULL ){
        // Delete it.
        delete helpText;
    }
}

// User event functions.
bool GameUI::LeftMouseDown( MousePos mousePos )
{
    return false;
}

bool GameUI::LeftMouseUp( MousePos mousePos )
{
    return false;
}

bool GameUI::RightMouseDown( MousePos mousePos )
{
    return false;
}

bool GameUI::DragCycle( MousePos mousePos ){
    return false;
}

bool GameUI::RightMouseUp( MousePos mousePos )
{
    LOG << "\r\nDISPLAYING HELP1";
    
    // If this was a click.
    if( IsClick() ){
        LOG << "\r\nISCLICK TRUE";
        // Display the boxe's help.
        DisplayHelp( true, mousePos.x, mousePos.y );
    }
    
    return false;
}

bool GameUI::WheelUp( MousePos mousePos )
{
    return false;
}

bool GameUI::WheelDown( MousePos mousePos )
{
    return false;
}


bool GameUI::TextInput( char ch )
{
    return false;
}

bool GameUI::VKeyInput( VKey vKey )
{
    return false;
}

// Window child functions
//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::AddChild
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds a child to the user interface.
// 
(
 GameUI *childUI // The child to add.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Put in foreground
    childList.push_front( childUI );
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::RemoveChild
//////////////////////////////////////////////////////////////////////////////////////////
//  Removes a child from the user interface.
// 
(
 GameUI *childUI // The child to find and remove.
)
//////////////////////////////////////////////////////////////////////////////////////////
{        
    // Find the child in the list.
    ChildQueue::iterator i = find( childList.begin(), childList.end(), childUI );

    // If the child was found.
    if( i != childList.end() ){
        // Erase it from the child list.
        childList.erase( i );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::DeleteChild
//////////////////////////////////////////////////////////////////////////////////////////
//  Removes a child from the user interface and deletes it from memory.
// 
(
 GameUI *childUI // The child to find and delete.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Remove the child
    RemoveChild( childUI );

    // Delete it.
    delete childUI;
}

//////////////////////////////////////////////////////////////////////////////////////////
GameUI *GameUI::GetRoot( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the root box object.
// 
// Return: GameUI, the root box.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return RootBoxUI::GetInstance();
}


// Drawing functions.
//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::Draw( V2SPRITEFX *vsfFX)
//////////////////////////////////////////////////////////////////////////////////////////
// Draws this box and all its children.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If the box isn't hidden.
    if( IsShown() ){    
        // If the box is minimized
        if( minimizedState )
        {
            // Call the draw minimized.
            DrawMinimized( vsfFX );
        }
        else
        {
            // If this box has a spriteId.
            if( !spriteId.empty())
            {
                // Draw this box. 
               if(!bDrawBlending )
                   vsfSprite.DrawSpriteN( framePos.x, framePos.y, vsfFX);
               else
                  vsfSprite.DrawSpriteNSemiTrans( framePos.x, framePos.y, vsfFX ,g_SaveGame.GetOptionsParam()->bGuiAlpha,g_Global.GetAlphaValue());
            }

            // Draw all childrens in reverse order.
            ChildQueue::reverse_iterator i;
            for( i = childList.rbegin(); i != childList.rend(); i++ )
            {
                if( (*i)->IsShown() && (*i) != SideMenu::GetInstance() )
                {
                   (*i)->Draw( vsfFX );// Draw this child.
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::DrawHelp
//////////////////////////////////////////////////////////////////////////////////////////
// Draws the help text. Virtual to allow functions to override help text display.
// 
(
 V2SPRITEFX *vsfFX // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If help is to be displayed
    if( helpDisplayState ){

        // If the mouse is not too far away from its original pos.
        if( ( abs( MouseDevice::xPos - helpInitialX ) * 2 +
            abs( MouseDevice::yPos - helpInitialY ) * 2 ) < 10*10
        ){
            // If a help fontized text was provided for this control.
            if( helpText != NULL ){
                // Draw the help at its last position. Never clip help.
                helpText->Draw( helpDisplayX, helpDisplayY - helpText->GetHeight() - 2, NULL );
            }
        }else{
            // Stop displaying help.
            helpDisplayState = false;
        }
    }

    // Draw all children's help.
    ChildQueue::iterator i;
    for( i = childList.begin(); i != childList.end(); i++ ){
        // Draw this child.
        (*i)->DrawHelp( vsfFX );
    }

}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::DrawMinimized
//////////////////////////////////////////////////////////////////////////////////////////
//  Draws minimized UI. Default to drawing normally.
//
(
 V2SPRITEFX *vsfFX
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If the box isn't hidden.
    if( IsShown() )
    {    
       vsfSprite.DrawSpriteN( framePos.x, framePos.y, vsfFX);
       
       // Draw all children.
       ChildQueue::iterator i;
       for( i = childList.begin(); i != childList.end(); i++ )
       {
          // Draw this child.
          (*i)->Draw( vsfFX );
       }
    }
}

void GameUI::DrawAlpha(bool bAlpha)
{
   bDrawBlending = bAlpha;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::Hide( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the box into hidden mode.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Unload the UI's graphics.
    vsfSprite.Release();

    hiddenState = true;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::Show(bool putForeground)
{
    // If this box has a spriteId.
    if( !spriteId.empty() )
    {
        // Load the UI's graphic.
        vsfSprite.LoadSprite( spriteId.c_str() );
    }
    
    hiddenState = false;
}

void GameUI::ShowLoad(BYTE *pData, BYTE* pPal,int dwW, int dwH, bool putForeground/* = true */)
{
   vsfSprite.Release();
   vsfSprite.LoadSpriteData(pData,pPal,dwW,dwH);
   hiddenState = false;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool GameUI::IsShown( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the box's hidden state.
// 
// Return: bool, true if the box is hidden, false if displayed.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return !hiddenState;
}

// Accessors
//////////////////////////////////////////////////////////////////////////////////////////
FramePos GameUI::GetPos( void ) const
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the box position.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return framePos;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::SetPos
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the UI's frame pos.
// 
(
 FramePos newFramePos // the new frame pos.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    framePos = newFramePos;
}

// General functionnalities function.
//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::Minimize
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the box into minimized state.
// 
(
 bool newMinimizedState // The new minimized state.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( newMinimizedState == false ){ // steph false au lieu de true (true semble emp�cher l'affichage du premier menu si la ligne ChatterUI est activ�e)
        ChatterUI::GetInstance()->Hide();
        SideMenu::GetInstance()->Hide();
    }

    minimizedState = newMinimizedState;
}

//////////////////////////////////////////////////////////////////////////////////////////
unsigned long GameUI::GetUnitAt
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the ID of the unit found at the given mouse position, or 0 if none were found.
// 
(
 MousePos mousePos // The mouse position to query from.
)
// Return: unsigned long, the found ID.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return 0;
}

// Protected child functions.
//////////////////////////////////////////////////////////////////////////////////////////
GameUI::ChildQueue *GameUI::GetChildList( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the child list.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return &childList;
}

// Foreground request functions.
//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::RequestForegroundControl
//////////////////////////////////////////////////////////////////////////////////////////
// Requests that the given child stays in foreground. Being in foreground, the child
// will monopolize all events.
// 
(
 GameUI *child // The child to bring to foreground.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    foregroundChild = child;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::DismissForegroundControl( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Remove whatever is currently in foreground.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    foregroundChild = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool GameUI::IsForegroundControlled( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns true if there is currently a box in foreground.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return( foregroundChild != NULL );
}


//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::PutChildInForeground
//////////////////////////////////////////////////////////////////////////////////////////
//  Puts the given child in foreground.
// 
(
 GameUI *child // The child to put in foreground.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Find the child
    ChildQueue::iterator i = find( childList.begin(), childList.end(), child );

    // If the child was found.
    if( i != childList.end() ){
        // If the child isn't already at the beginning of list.
        if( i != childList.begin() ){
            // Erase it from its current position.
            childList.erase( i );

            // Add it to the front.
            childList.push_front( child );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::PutChildInBackground
//////////////////////////////////////////////////////////////////////////////////////////
//  Puts the given child in foreground.
// 
(
 GameUI *child // The child to put in foreground.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Find the child
    ChildQueue::iterator i = find( childList.begin(), childList.end(), child );

    // If the child was found.
    if( i != childList.end() ){
        // If the child isn't already at the beginning of list.
        if( i != childList.begin() ){
            // Erase it from its current position.
            childList.erase( i );

            // Add it to the back.
            childList.push_back( child );
        }
    }
}

// Static functions
// Global user event functions
//////////////////////////////////////////////////////////////////////////////////////////
bool GameUI::IsDblClick( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if the mouse is currently dbl-clicking.
// 
// Return: bool, true if the mouse is in dbl click mode.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( currentMouseState == MouseDblClick ){
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool GameUI::IsClick( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Determines if the mouse is currently clicking.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( currentMouseState == MouseClick ){
        return true;
    }
    return false;
}

// Global drag and drop functions.    
//////////////////////////////////////////////////////////////////////////////////////////
bool GameUI::SetDragItem
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the drag item. Fails if a drag is already in process.
// 
(
 GameUI       *newDragItem,
 EventVisitor *newDraggedVisitor,
 GameUI       *newDragParent,
 MousePos      newDragInitialPos
)
// Return: bool, true if the drag was successful.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If there wasn't any previous drag item.
    if( draggedItem == NULL ){
        draggedItem = newDragItem;
        draggedEvent = newDraggedVisitor;
        draggedParentUI = newDragParent;
        draggedInitialPos = newDragInitialPos;

        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
GameUI *GameUI::GetDragItem( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the currently dragged item. NULL if no item is currently being dragged.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    return draggedItem;
}

//////////////////////////////////////////////////////////////////////////////////////////
EventVisitor *GameUI::GetDragSourceEvent( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the dragged item visitor.
// 
// Return: EventVisitor, The item visitor or NULL if none was provided.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return draggedEvent;
}

//////////////////////////////////////////////////////////////////////////////////////////
GameUI *GameUI::GetDragParentUI( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the UI from which origninated the drag.
// 
// Return: GameUI, the source UI.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return draggedParentUI;
}

//////////////////////////////////////////////////////////////////////////////////////////
MousePos GameUI::GetDragInitialPos( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the original mouse position where the drag began.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    return draggedInitialPos;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::CancelDrag( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Cancels or stops dragging.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    draggedItem = NULL;
    draggedEvent = NULL;
    draggedParentUI = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::SetUIMouseCursor
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the mouse cursor to the given UI.
// 
(
 GameUI *gameUI, // The UI.
 int xOff,       // Additional x offset.
 int yOff        // Additional y offset.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    int xCor = -( gameUI->GetPos().Width()  / 2 );
    int yCor = -( gameUI->GetPos().Height() / 2 );

    // Create a custom cursor with the ui's graphic.
    CMouseCursor::GetInstance()->SetCustomCursor( gameUI->GetVSF(), xCor, yCor );

    MouseDevice mouseDevice;            
    mouseDevice.SetPosition( gameUI->GetPos().x + xOff - xCor, gameUI->GetPos().y + yOff - yCor );
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::ClientShutdown( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Called when the client shutdowns.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Call it for all children.
    ChildQueue::iterator i;
    
    for( i = childList.begin(); i != childList.end(); i++ ){
        (*i)->ClientShutdown();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::ClientInitialize( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Called when the client initializes.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    ChildQueue::iterator i;

    for( i = childList.begin(); i != childList.end(); i++ ){
        (*i)->ClientInitialize();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::DisplayHelp
//////////////////////////////////////////////////////////////////////////////////////////
//  Set the UI's help display on.
// 
(
 bool newDisplayState, // The new display state.
 int x, // Display x coor.
 int y  // Display y coor.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    //##NMNMNM [ToolTips afficher]
    helpDisplayState = newDisplayState;
    helpDisplayX = x;
    helpDisplayY = y;
    helpInitialX = x;
    helpInitialY = y;
    
    if( helpText != NULL )
    {
        int maxX = 250;
        if( helpDisplayX + maxX >= g_Global.GetScreenW() )
        {
            maxX = g_Global.GetScreenW() - helpDisplayX;
        }

        if(helpDisplayX+250 > g_Global.GetScreenW())
        {
           if( helpDisplayX+helpText->GetWidth() > g_Global.GetScreenW() )
           {
              int minX  = g_Global.GetScreenW()-250;
              if(helpText->GetWidth() <250)
                 minX  = g_Global.GetScreenW()-helpText->GetWidth();

               helpDisplayX = minX;
               maxX = g_Global.GetScreenW() - minX;
           }
        }
        
        helpText->Format( maxX );

        if( helpDisplayY - helpText->GetHeight() < 0 )
        {
            helpDisplayY = helpText->GetHeight();
        }

    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::ResyncHelpText( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Resynchronizes the help text (if it was changed in real-time).
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( helpDisplayState && helpText != NULL ){
        int maxX = 250;
        if( helpDisplayX + maxX >= 640 ){
            maxX = 640 - helpDisplayX;
        }

        helpText->Format( maxX );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
bool GameUI::IsParent
//////////////////////////////////////////////////////////////////////////////////////////
//  Determines if the given GameUI is the parent if this UI.
// 
(
 GameUI *parent, // The 'perhaps' parent ui.
 GameUI *child   // The child wanting to know.
)
// Return: bool, true if test is this's parent.
//////////////////////////////////////////////////////////////////////////////////////////
{
    
    ChildQueue::iterator i;
    for( i = parent->childList.begin(); i != parent->childList.end(); i++ ){        
        if( (*i) == child ){
            return true;
        }
        
        if( IsParent( (*i), child ) ){
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool GameUI::IsLeftMouseDown( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
    return leftMouseDown;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GameUI::SetSpriteId
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the gameUI's sprite ID.
// 
(
 std::string newSpriteId
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    spriteId = newSpriteId;
}

//////////////////////////////////////////////////////////////////////////////////////////
std::string GameUI::GetSpriteId( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the GameUI's current sprite Id.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    return spriteId;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool GameUI::IsSpriteDefined( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns true if a sprite was set for this game UI.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( !spriteId.empty() ){
        return true;
    }
    return false;
}
