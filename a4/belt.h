

#ifndef BELT_H
#define BELT_H

#include "mystruct.h"

// global variables, not for use in threads
int produced; // total produced
int CFBnum;
int EESnum;

int lucyCFB;
int lucyEES;

int ethelCFB;
int ethelEES;

void produce(ProductType candy, Link * head);

ProductType consume(ConsumerType consumer, Link * head);

int candycount(ProductType candy, Link head);

void printlist(Link ptr);

void printupdate(Link head);

void printreport();

#endif