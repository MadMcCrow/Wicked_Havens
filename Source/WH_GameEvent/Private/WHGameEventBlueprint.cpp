// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "GameEvent/WHGameEventBlueprint.h"

UWHGameEventBlueprint::UWHGameEventBlueprint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

#if WITH_EDITOR
UClass* UWHGameEventBlueprint::GetBlueprintClass() const
{
	return UBlueprintGeneratedClass::StaticClass();
}

bool UWHGameEventBlueprint::ValidateGeneratedClass(const UClass* InClass)
{
	const UBlueprintGeneratedClass* GeneratedClass = Cast<const UBlueprintGeneratedClass>(InClass);
	if ( !ensure(GeneratedClass) )
	{
		return false;
	}
	const UWHGameEventBlueprint* Blueprint = Cast<UWHGameEventBlueprint>(GetBlueprintFromClass(GeneratedClass));
	if ( !ensure(Blueprint) )
	{
		return false;
	}

	return true;
}
#endif
