#include "TGAnimationManager.h"
#include "TGSqliteQuery.h"
//#include <stdint.h>
//---------------------------------------------------------------------
TGAnimationManager::TGAnimationManager()
{

}
//---------------------------------------------------------------------
TGAnimationManager::~TGAnimationManager()
{

}
//---------------------------------------------------------------------
void TGAnimationManager::LoadAnimations(PTGBaseTextureManager texture_manager)
{
	TGSqliteQuery animations_query;
	TGDataRecord schema;
	animations_query.Exec(
		TGSqlite::GetMainDatabase(), 
		QString("select * from Animations order by \"Order\""), 
		&schema);

	TGDataRecord data;
	while (animations_query.Read(&data))
	{
		TGAnimationPhase phase;
		UID image = data[1].toInt();
		UID animation_id = data[3].toInt(); 

		phase.Delay = data[2].toInt();
		phase.Image = texture_manager->GetBaseTexture(image);

		Animations[animation_id].push_back(phase);
	}	

	LoadStates();
}
//---------------------------------------------------------------------
void TGAnimationManager::LoadStates()
{
	TGSqliteQuery state_query;
	TGDataRecord schema;
	state_query.Exec(
		TGSqlite::GetMainDatabase(), 
		QString("select * from States"), 
		&schema);

	TGDataRecord data;
	while (state_query.Read(&data))
	{
		TGObjectState state;
		UID id = data[0].toInt();
		UID animation_id = data[1].toInt(); 
		state.MousePushed = data[2].toInt();
		state.MouseHover = data[3].toInt();
		state.Animation = Animations[animation_id];
		States[id].push_back(state);
	}	

}
//---------------------------------------------------------------------
TGObjectsStateList TGAnimationManager::GetState(UID state_id)
{
	return States[state_id];
}
//---------------------------------------------------------------------
