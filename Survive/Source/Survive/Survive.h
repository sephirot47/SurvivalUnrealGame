// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

//In order to extend from UUserWidget
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "SUtils.h"

//Defined in Survive.h
#define BuildableObjectType ECC_GameTraceChannel2
//Defined in Survive.h
#define PlayerPointingTraceChannel ECC_GameTraceChannel4
//Defined in Survive.h
#define PlayerMovingTraceChannel   ECC_GameTraceChannel1