#pragma once
#include "IntSetProblem.h"
#include <iostream>


void GameStep(IntSet& state, OrderedPair action);

void IntSetPlay(const FMDP::Actor<IntSet, OrderedPair>& player, const IntSetEnviroment& enviroment, IntSet state);