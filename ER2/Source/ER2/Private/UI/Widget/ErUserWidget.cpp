// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ErUserWidget.h"

void UErUserWidget::SetWidgetController(UObject* InWidgetController)
{
    WidgetController = InWidgetController;
    WidgetControllerSet();
}
