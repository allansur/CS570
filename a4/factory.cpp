#include "production.h"

/// link-list for belt 

int produced; // total produced
int frog_total;
int escar_total;

int L_frog_total;
int L_escar_total;

int E_frog_total;
int E_escar_total;

void produce(ProductType candy_type, Link * head);

ProductType consume(ConsumerType consumer, Link * head);

int candycount(ProductType candy_type, Link head);

