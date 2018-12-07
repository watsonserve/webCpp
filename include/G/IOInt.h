//
//  IOInt.h
//  GHTTPd
//
//  Created by 王兴卓 on 18/9/22.
//  Copyright © 2018年 watsserve. All rights reserved.
//

#ifndef _IOINT_H_
#define _IOINT_H_

#include "stdafx.h"

static unsigned long epfd;

int IOInt(struct aioinit * aip);
void* listenEvent(void *);


#endif /* _IOINT_H_ */
