// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HJCrosshairWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

void UHJCrosshairWidget::NativeConstruct()
{
    Super::NativeConstruct();

    int32 ViewportX, ViewportY;
    if (GetWorld() && GetWorld()->GetFirstPlayerController())
    {
        GetWorld()->GetFirstPlayerController()->GetViewportSize(ViewportX, ViewportY);
        ViewportCenterOffset = FVector2D(ViewportX / 2.0f, ViewportY / 2.0f);
    }
}

void UHJCrosshairWidget::SetCrosshairPosition(const FVector2D& ScreenPosition)
{
    if (CrosshairImage)
    {
 /*       UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(CrosshairImage->Slot);
        if (CanvasSlot)
        {
            CanvasSlot->SetPosition(ScreenPosition - ViewportCenterOffset);
        }*/

           CrosshairImage->SetRenderTranslation(ScreenPosition - ViewportCenterOffset);
        
    }
}

void UHJCrosshairWidget::ResetCrossharPosition()
{
    FVector2D ResetVector2D = {};
    if (CrosshairImage)
    {
        CrosshairImage->SetRenderTranslation(ResetVector2D);

    }
}
