/*
----------------------------------------------------------
Program: program4.c
Date: September 12, 2023
Student Name & NetID: Kennedy Keyes kfk38
Description: This program opens the input file, "angl.dat", 
to read one set of roll, pitch, and yaw values each second. 
Then, it should verify if each the roll and pitch are inside
the range of -20.0 to 20.0 and report the results. Then closes.
----------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>

#define RANGE_LOWER -20.0
#define RANGE_UPPER 20.0

int testError(int val, const char *msg)
{
  if (val == -1) 
  {
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return val;
}

int main(int argc, char *argv[])
{
  int fd, rd;
  double roll, pitch, yaw;
  struct timespec ts;
  ts.tv_sec = 1;
  ts.tv_nsec = 0;

  fd = testError(open("angl.dat", O_RDONLY), "open"); // opens the input file for reading

  while (1)
  { // reads roll, pitch, and yaw values from the input file, one triple at a time
    rd = testError(read(fd, &roll, sizeof(double)), "read");
    rd = testError(read(fd, &pitch, sizeof(double)), "read");
    rd = testError(read(fd, &yaw, sizeof(double)), "read");
    if (rd <= 0) break;
  
    printf("Roll: %.03lf, Pitch: %.03lf, Yaw: %.03lf\n", roll, pitch, yaw); // prints the values to the monitor

    if (roll >= RANGE_LOWER && roll <= RANGE_UPPER && pitch >= RANGE_LOWER && pitch <= RANGE_UPPER)
    {
      printf("Roll: %.03lf, Pitch: %.03lf are inside the range\n", roll, pitch); // if the roll and pitch values are within the range, output this
    }
    else
    {
      printf("Roll: %.03lf, Pitch: %.03lf are outside the range\n", roll, pitch); // if the roll and pitch values are NOT within the range, output this
    }

    nanosleep(&ts, NULL);
  }

  close(fd); 

  exit(EXIT_SUCCESS);
}
