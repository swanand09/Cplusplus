/*
	Nazara Engine - DynaTerrain

	Copyright (C) 2012 Rémi "Overdrivr" Bèges (remi.beges@laposte.net)

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	of the Software, and to permit persons to whom the Software is furnished to do
	so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#pragma once

#ifndef NAZARA_CONFIG_DYNATERRAIN_HPP
#define NAZARA_CONFIG_DYNATERRAIN_HPP

/// Chaque modification d'un paramètre du module nécessite une recompilation de celui-ci

// Utilise un tracker pour repérer les éventuels leaks (Ralentit l'exécution)
#define NAZARA_DYNATERRAIN_MEMORYLEAKTRACKER 1

// Active les tests de sécurité basés sur le code (Conseillé pour le développement)
#define NAZARA_DYNATERRAIN_SAFE 1

// La profondeur maximale de subdivision du terrain (le node le plus petit est 2^-n fois plus petit que le terrain)
// TODO : A UTILISER
#define NAZARA_DYNATERRAIN_MAXIMUM_TERRAIN_DEPTH 20

#endif // NAZARA_CONFIG_MODULENAME_HPP
