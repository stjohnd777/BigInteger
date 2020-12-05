/*
 * common.h
 *
 *  Created on: May 28, 2020
 *      Author: local-admin
 */

#pragma once

#define DEBUG 1
/*
 * Create get<funName>/set<funName> for instance varable of
 * type <varType> and name <varName> with initial value v
 *
 */
#define GETTERSETTER(varType, varName, funName)\
    protected: varType varName ;\
    public: virtual varType get##funName(void) const {\
        return varName;\
    }\
    public: virtual void set##funName(varType v){\
        varName =v;\
    }\

#define ATTRV(varType, varName, funName, v)\
    protected: varType varName = v ;\
    public: virtual varType get##funName(void) const {\
        return varName;\
    }\
    public: virtual void set##funName(varType var){\
        varName = var;\
    }\






