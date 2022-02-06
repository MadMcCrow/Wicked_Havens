// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "Engine/Blueprint.h"
#include "WHGameEventBlueprint.generated.h"

/**
 * The GameEvent Blueprint class
 * This exists mostly to have custom assets in editor
 */
UCLASS(BlueprintType)
class WH_GAMEEVENT_API UWHGameEventBlueprint : public UBlueprint
{
	GENERATED_BODY()
public:

	UWHGameEventBlueprint(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
	virtual UClass* GetBlueprintClass() const override;
	virtual bool SupportedByDefaultBlueprintFactory() const override
	{
		return true;
	}

	static bool ValidateGeneratedClass(const UClass* InClass);
#endif
};
