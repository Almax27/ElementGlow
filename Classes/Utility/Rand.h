/*
 * Rand.h
 *
 *  Created on: 15 Oct 2013
 *      Author: Almax
 */

#ifndef RAND_H_
#define RAND_H_

#include <stdlib.h>

#define randf01() ((float)std::rand()/(float)RAND_MAX)
#define randf(min,max) ((min) + (float)std::rand()/((float)RAND_MAX/((max)-(min))))
#define randi(min,max) (int)((min) + std::rand()/(RAND_MAX/((max)-(min))))
#define randSign() (randf01() > 0.5f ? 1 : -1)

#endif /* RAND_H_ */
