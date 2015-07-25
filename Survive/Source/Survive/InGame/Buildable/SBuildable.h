#pragma once

#include "GameFramework/Actor.h"
#include "../IDamageReceiver.h"
#include "SBuildable.generated.h"

UENUM(BlueprintType)
enum BuildableState
{
	Building,		  //When the player is positioning this building
	Built,			  //Default state
	PointingOver     //When the player is pointing this building
};

UCLASS()
class SURVIVE_API ASBuildable : public AActor, public IDamageReceiver
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere) UMaterial *onBuildingMaterial;
	UPROPERTY(EditAnywhere) UMaterial *onWrongBuildingMaterial;
	UPROPERTY(EditAnywhere) UMaterial *onBuiltMaterial;
	UPROPERTY(EditAnywhere) UMaterial *onPointingOverMaterial;
	UPROPERTY(EditAnywhere) UMaterial *onSelectedMaterial;

	UMaterial *lastMaterial;

	BuildableState currentState;

	float rotationSpeed;
	int overlaps;

	void ChangeMaterial(UMaterial *material);
	bool IsOverlapping() { return overlaps > 0; }

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float life;

	ASBuildable();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintNativeEvent, Category = BuildableState)
		void OnBuilding();

	UFUNCTION(BlueprintNativeEvent, Category = BuildableState)
		void OnBuilt();

	UFUNCTION(BlueprintNativeEvent, Category = BuildableState)
		void OnPointingOver();

	UFUNCTION(BlueprintNativeEvent, Category = BuildableState)
		void OnDestroy();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		BuildableState GetCurrentState();

	UFUNCTION()
		void OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetCollidableWithPlayer(bool collidableWithPlayer);

	inline bool CanBeBuilt() { return !IsOverlapping(); }
	inline float GetRotationSpeed() { return rotationSpeed; }

	virtual void ReceiveDamage(AActor* originActor, float damage) override;

	UFUNCTION(BlueprintNativeEvent, Category = Damage)
		void OnReceiveDamage(AActor* originActor, float damage);
};
