/*******************************************************************************************
*
*   Physics v1.0.0 - Physics
*
*   MODULE USAGE:
*       #define GUI_PHYSICS_IMPLEMENTATION
*       #include "gui_physics.h"
*
*       INIT: GuiPhysicsState state = InitGuiPhysics();
*       DRAW: GuiPhysics(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 Colton Clark. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_PHYSICS_H
#define GUI_PHYSICS_H

#define GUI_TEXT(data) TextFormat("%0.2f", data)

typedef struct {
    Vector2 anchor01;
    Vector2 anchor02;
    
    bool PhysicsPanelActive;
    float BodyMassValue;
    float BodySizeValue;
    float BodyGravityValue;
    float BodyRestitutionValue;
    float BodyDampingValue;
    bool BodyTypeEditMode;
    int BodyTypeActive;
    float SpringStiffnessValue;
    float SpringDampingValue;
    bool SpringAutoLengthChecked;
    float SpringLengthValue;
    bool EffectorTypeEditMode;
    int EffectorTypeActive;
    float EffectorSizeValue;
    float EffectorForceValue;
    float EffectorAngleValue;
    bool SimulateActive;
    float GravityValue;
    float FPSValue;
    float BodyVelocityValue;
    float SpringMultiplierValue;
    bool WindowBox023Active;

    Rectangle layoutRecs[24];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiPhysicsState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiPhysicsState InitGuiPhysics(void);
void GuiPhysics(GuiPhysicsState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_PHYSICS_H

/***********************************************************************************
*
*   GUI_PHYSICS IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_PHYSICS_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiPhysicsState InitGuiPhysics(void)
{
    GuiPhysicsState state = { 0 };

    state.anchor01 = Vector2{ 1256, 728 };
    state.anchor02 = Vector2{ 24, 40 };
    
    state.PhysicsPanelActive = true;
    state.BodyMassValue = 0.5f;
    state.BodySizeValue = 0.5f;
    state.BodyGravityValue = 1.0f;
    state.BodyRestitutionValue = 0.5f;
    state.BodyDampingValue = 0.1f;
    state.BodyTypeEditMode = false;
    state.BodyTypeActive = 0;
    state.SpringStiffnessValue = 5.0f;
    state.SpringDampingValue = 2.0f;
    state.SpringAutoLengthChecked = true;
    state.SpringLengthValue = 5.0f;
    state.EffectorTypeEditMode = false;
    state.EffectorTypeActive = 0;
    state.EffectorSizeValue = 0.0f;
    state.EffectorForceValue = 0.0f;
    state.EffectorAngleValue = 0.0f;
    state.SimulateActive = true;
    state.GravityValue = -9.81f;
    state.FPSValue = 60.0f;
    state.BodyVelocityValue = 5.0f;
    state.SpringMultiplierValue = 0.0f;
    state.WindowBox023Active = true;

    state.layoutRecs[0] = Rectangle{ state.anchor02.x + 0, state.anchor02.y + 0, 304, 664 };
    state.layoutRecs[1] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 112, 184, 16 };
    state.layoutRecs[2] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 88, 184, 16 };
    state.layoutRecs[3] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 136, 184, 16 };
    state.layoutRecs[4] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 160, 184, 16 };
    state.layoutRecs[5] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 184, 184, 16 };
    state.layoutRecs[6] = Rectangle{ state.anchor02.x + 32, state.anchor02.y + 48, 240, 24 };
    state.layoutRecs[7] = Rectangle{ state.anchor02.x + 8, state.anchor02.y + 256, 296, 120 };
    state.layoutRecs[8] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 272, 184, 16 };
    state.layoutRecs[9] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 296, 184, 16 };
    state.layoutRecs[10] = Rectangle{ state.anchor02.x + 104, state.anchor02.y + 344, 16, 16 };
    state.layoutRecs[11] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 320, 184, 16 };
    state.layoutRecs[12] = Rectangle{ state.anchor02.x + 8, state.anchor02.y + 392, 296, 136 };
    state.layoutRecs[13] = Rectangle{ state.anchor02.x + 32, state.anchor02.y + 408, 240, 24 };
    state.layoutRecs[14] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 448, 184, 16 };
    state.layoutRecs[15] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 472, 184, 16 };
    state.layoutRecs[16] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 496, 184, 16 };
    state.layoutRecs[17] = Rectangle{ state.anchor02.x + 32, state.anchor02.y + 624, 240, 24 };
    state.layoutRecs[18] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 568, 184, 16 };
    state.layoutRecs[19] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 544, 184, 16 };
    state.layoutRecs[20] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 208, 184, 16 };
    state.layoutRecs[21] = Rectangle{ state.anchor02.x + 8, state.anchor02.y + 32, 296, 208 };
    state.layoutRecs[22] = Rectangle{ state.anchor02.x + 80, state.anchor02.y + 592, 184, 16 };
    state.layoutRecs[23] = Rectangle{ state.anchor01.x + 0, state.anchor01.y + 0, 120, 48 };

    // Custom variables initialization

    return state;
}

void GuiPhysics(GuiPhysicsState *state)
{
    if (state->BodyTypeEditMode || state->EffectorTypeEditMode) GuiLock();

    if (state->PhysicsPanelActive)
    {
        state->PhysicsPanelActive = !GuiWindowBox(state->layoutRecs[0], "PHYSICS CONTROLS");
        GuiSliderBar(state->layoutRecs[1], "MASS", GUI_TEXT(&state->BodyMassValue), &state->BodyMassValue, 0, 1);
        GuiSliderBar(state->layoutRecs[2], "SIZE", GUI_TEXT(&state->BodySizeValue), &state->BodySizeValue, 0, 1);
        GuiSliderBar(state->layoutRecs[3], "GRAVITY", GUI_TEXT(&state->BodyGravityValue), &state->BodyGravityValue, -10, 10);
        GuiSliderBar(state->layoutRecs[4], "BOUNCE", GUI_TEXT(&state->BodyRestitutionValue), &state->BodyRestitutionValue, 0, 10);
        GuiSliderBar(state->layoutRecs[5], "DAMPING", GUI_TEXT(&state->BodyDampingValue), &state->BodyDampingValue, 0, 10);
        GuiGroupBox(state->layoutRecs[7], "SPRING");
        GuiSliderBar(state->layoutRecs[8], "STIFFNESS", GUI_TEXT(&state->SpringStiffnessValue), &state->SpringStiffnessValue, 0, 10);
        GuiSliderBar(state->layoutRecs[9], "DAMPING", GUI_TEXT(&state->SpringDampingValue), &state->SpringDampingValue, 0, 10);
        GuiCheckBox(state->layoutRecs[10], "AUTO LENGTH", &state->SpringAutoLengthChecked);
        GuiSliderBar(state->layoutRecs[11], "LENGTH", GUI_TEXT(&state->SpringLengthValue), &state->SpringLengthValue, 0, 10);
        GuiGroupBox(state->layoutRecs[12], "EFFECTOR");
        GuiSliderBar(state->layoutRecs[14], "SIZE", GUI_TEXT(&state->EffectorSizeValue), &state->EffectorSizeValue, 0, 5);
        GuiSlider(state->layoutRecs[15], "FORCE", GUI_TEXT(&state->EffectorForceValue), &state->EffectorForceValue, 0, 10);
        GuiSliderBar(state->layoutRecs[16], "ANGLE", GUI_TEXT(&state->EffectorAngleValue), &state->EffectorAngleValue, 0, 10);
        GuiToggle(state->layoutRecs[17], "SIMULATE", &state->SimulateActive);
        GuiSlider(state->layoutRecs[18], "GRAVITY", GUI_TEXT(&state->GravityValue), &state->GravityValue, -10, 10);
        GuiSliderBar(state->layoutRecs[19], "FPS", GUI_TEXT(&state->FPSValue), &state->FPSValue, 10, 120);
        GuiSliderBar(state->layoutRecs[20], "VELOCITY", GUI_TEXT(&state->BodyVelocityValue), &state->BodyVelocityValue, 0, 10);
        GuiGroupBox(state->layoutRecs[21], "BODY");
        GuiSliderBar(state->layoutRecs[22], "SPRING X", GUI_TEXT(&state->SpringMultiplierValue), &state->SpringMultiplierValue, 0, 10);
        if (GuiDropdownBox(state->layoutRecs[6], "DYNAMIC;KINEMATIC;STATIC", &state->BodyTypeActive, state->BodyTypeEditMode)) state->BodyTypeEditMode = !state->BodyTypeEditMode;
        if (GuiDropdownBox(state->layoutRecs[13], "GRAVITATION;POINT;AREA;DRAG", &state->EffectorTypeActive, state->EffectorTypeEditMode)) state->EffectorTypeEditMode = !state->EffectorTypeEditMode;
    }
    if (state->WindowBox023Active)
    {
        state->WindowBox023Active = !GuiWindowBox(state->layoutRecs[23], "SAMPLE TEXT");
    }
    
    GuiUnlock();
}

#endif // GUI_PHYSICS_IMPLEMENTATION
