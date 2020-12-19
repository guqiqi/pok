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


#include <libc/stdio.h>
#include <core/thread.h>
#include <core/semaphore.h>
#include <core/time.h>
#include <types.h>
#include "activity.h"

extern uint8_t sid;
uint8_t val;

int getC(){
   int ch;
   while((ch = getChar()) == -1){
   }
   printf("your enter: %d\n", ch);
   return ch;
}

void* pinger_job1 ()
{
   pok_ret_t ret;
   while (1)
   {
      // printf ("P1T1: I will signal semaphores\n");
      // ret = pok_sem_signal (sid);
      // printf ("P1T1: pok_sem_signal, ret=%d\n", ret);
      int a = getC();
      pok_thread_sleep (10000);
   }
}


void* pinger_job2 ()
{
   pok_ret_t ret;
   while (1)
   {
      printf ("P1T2: I will signal semaphores\n");
      ret = pok_sem_signal (sid);
      printf ("P1T2: pok_sem_signal, ret=%d\n", ret);
      pok_thread_sleep (10000);
   }
}

void* pinger_job3 ()
{
   pok_ret_t ret;
   uint8_t tid;
   pok_thread_attr_t     tattr;
   pok_time_t time_t;
   uint8_t  add_task = 0;
   while (1)
   {
      printf ("P1T3: I will wait for the semaphores\n");
      ret = pok_sem_wait (sid, 0);
      printf ("P1T3: pok_sem_wait, ret=%d\n", ret);

      ret = pok_time_gettick(&time_t);
      printf("time %d\n", time_t);

      if(add_task == 0 && time_t > 40000000){
         tattr.priority = 4;
         tattr.time_capacity = 2;
         tattr.deadline = 3;
         tattr.period = 500000000;
         tattr.weight = 2;
         tattr.entry = pinger_job4;

         ret = pok_partition_thread_add(&tid , &tattr);
         
         add_task = add_task + 1;
      }

      if(add_task == 1 && time_t > 80000000){
         tattr.priority = 4;
         tattr.time_capacity = 2;
         tattr.deadline = 1;
         tattr.period = 500000000;
         tattr.weight = 2;
         tattr.entry = pinger_job5;

         ret = pok_partition_thread_add(&tid , &tattr);
         
         add_task = add_task + 1;
      }

      pok_thread_sleep (10000);
   }
}

void* pinger_job4 ()
{
   pok_ret_t ret;
   while (1)
   {
      printf ("P1T4: I will signal semaphores\n");
      ret = pok_sem_signal (sid);
      printf ("P1T4: pok_sem_signal, ret=%d\n", ret);
      pok_thread_sleep (10000);
   }
}

void* pinger_job5 ()
{
   pok_ret_t ret;
   while (1)
   {
      printf ("P1T5: I will wait for the semaphores\n");
      ret = pok_sem_wait (sid, 0);
      printf ("P1T5: pok_sem_wait, ret=%d\n", ret);
      pok_thread_sleep (10000);
   }
}
