#ifndef SUPPLIERS_H
#define SUPPLIERS_H

/* entry point called from main.c */
void supplierMenu(void);

/* getters used by reports.c - DO NOT change these signatures */
int getSupplierCount(void);
const char* getSupplierName(int i);
const char* getSupplierTown(int i);

#endif
