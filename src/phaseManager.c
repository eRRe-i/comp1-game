#include "common.h"
#include "map.h"
#include "player.h"
#include "phaseManager.h"

PhaseManager* loadPhaseManager() {

    PhaseManager* phaseManager = (PhaseManager*)malloc(sizeof(PhaseManager));
    phaseManager->mapIndex = 0;
    return phaseManager;

}
