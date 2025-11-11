#ifndef UNAME_H
#define UNAME_H

void log_uname(void) {
  FILE *fp;
  const char* cmd = "uname -a";
  fp = popen(cmd, "r");
  if (fp == NULL) {
    printf("Failed to run command\n");
    exit(1);
  }
  char output[1024];
  while (fgets(output, sizeof(output), fp)) {
    syslog(LOG_INFO, "%s", output);
  }
  pclose(fp);
}

#endif // UNAME_H
