#include "StartGameSuccess.h"

#include <utility>

StartGameSuccess::StartGameSuccess(std::vector<Player> players, uuid startingPlayerId)
    : ServerResponse(ResponseType::StartGameSuccess), players(std::move(players)), startingPlayerId(startingPlayerId) {}