
#include "Widgets/UI/ValueGauge.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UValueGauge::NativeConstruct()
{
	Super::NativeConstruct();
	
	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue) const
{
	if (NewMaxValue == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Value Gauge: %s, NewMaxValue can't be 0"), *GetName());
		return;
	}
	
	const float NewPercent = NewValue / NewMaxValue;
	ProgressBar->SetPercent(NewPercent);
	
	const FNumberFormattingOptions FormatOps = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	
	ValueText->SetText(
		FText::Format(
			FTextFormat::FromString("{0}/{1}"),
			FText::AsNumber(NewValue, &FormatOps),
			FText::AsNumber(NewMaxValue, &FormatOps)
		)
	);
}
