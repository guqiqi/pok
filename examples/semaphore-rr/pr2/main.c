/*
 *                               POK header
 * 
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2009 POK team 
 *
 * Created by julien on Thu Jan 15 23:34:13 2009 
 */


#include <core/thread.h>
#include <core/partition.h>
#include <types.h>
#include "activity.h"


int main ()
{
 uint8_t tid;
  pok_ret_t ret;
  pok_thread_attr_t     tattr;

  tattr.priority = 1;
  tattr.arrive_time = 0;
  tattr.time_capacity = 2;
  tattr.deadline = 2;
  tattr.period = 500000000;
  tattr.weight = 2;
  tattr.entry = pinger_job1;

  ret = pok_thread_create(&tid , &tattr);
  printf("[P2] pok_thread_create (1) return=%d\n", ret);

  tattr.priority = 3;
  tattr.arrive_time = 0;
  tattr.time_capacity = 4;
  tattr.deadline = 11;
  tattr.period = 500000000;
  tattr.weight = 4;
  tattr.entry = pinger_job2;

  ret = pok_thread_create(&tid , &tattr);
  printf("[P2] pok_thread_create (2) return=%d\n", ret);

  tattr.priority = 3;
  tattr.arrive_time = 0;
  tattr.time_capacity = 6;
  tattr.deadline = 9;
  tattr.period = 500000000;
  tattr.weight = 6;
  tattr.entry = pinger_job3;

  ret = pok_thread_create(&tid , &tattr);
  printf("[P2] pok_thread_create (3) return=%d\n", ret);

  pok_partition_set_mode (POK_PARTITION_MODE_NORMAL);
  pok_thread_wait_infinite ();

   return (0);
}


