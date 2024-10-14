#include "storage.h"

#define TAG "STOR"
static FILE *f;

static esp_err_t s_example_write_file(const char *path, char *data) {
  ESP_LOGI(TAG, "Opening file %s", path);
  FILE *_f = fopen(path, "w");
  if (_f == NULL) {
    ESP_LOGE(TAG, "Failed to open file for writing");
    return ESP_FAIL;
  }
  fprintf(_f, data);
  fclose(_f);
  ESP_LOGI(TAG, "File written");

  return ESP_OK;
}

static esp_err_t s_example_read_file(const char *path) {
  ESP_LOGI(TAG, "Reading file %s", path);
  FILE *_f = fopen(path, "r");
  if (_f == NULL) {
    ESP_LOGE(TAG, "Failed to open file for reading");
    return ESP_FAIL;
  }
  char line[EXAMPLE_MAX_CHAR_SIZE];
  fgets(line, sizeof(line), _f);
  fclose(_f);

  // strip newline
  char *pos = strchr(line, '\n');
  if (pos) {
    *pos = '\0';
  }
  ESP_LOGI(TAG, "Read from file: '%s'", line);

  return ESP_OK;
}

void storage_init(char *_fn) {
  ESP_LOGI(TAG, "Init storage");
  char fn[32] = SD_MOUNT "/" STOR_PREFIX "0000.txt";
  f = NULL;
  if (_fn == NULL) {
    uint16_t i = 0;
    struct stat st;
    while (stat(fn, &st) == 0) sprintf(fn, SD_MOUNT "/" STOR_PREFIX "%04d.txt", ++i);
    f = fopen(fn, "a+");
  } else {
    f = fopen(_fn, "a+");
  }
  if (f == NULL) esp_restart();
  printf("Open %s %d\n", fn, fileno(f));
}

void storage_write(char *data) {
  fprintf(f, data);
  return;
}

void storage_read() {
  char line[EXAMPLE_MAX_CHAR_SIZE];
  fgets(line, sizeof(line), f);

  // strip newline
  char *pos = strchr(line, '\n');
  if (pos) {
    *pos = '\0';
  }
  return;
}

void storage_flush() {
  if (f == NULL) return;
  fflush(f);
  fsync(fileno(f));
}

FILE *storage_fetch() { return f; }

void storage_demo(void) {
  esp_err_t ret;

  ESP_LOGI(TAG, "Filesystem mounted");

  // First create a file.
  const char *file_hello = SD_MOUNT "/hello.txt";
  char *source = "Hello";
  char data[EXAMPLE_MAX_CHAR_SIZE];
  strcpy(data, source);
  // snprintf(data, EXAMPLE_MAX_CHAR_SIZE, "%s %s!\n", "Hello", card->cid.name);
  ret = s_example_write_file(file_hello, data);
  if (ret != ESP_OK) {
    return;
  }

  const char *file_foo = SD_MOUNT "/foo.txt";

  // Check if destination file exists before renaming
  struct stat st;
  if (stat(file_foo, &st) == 0) {
    // Delete it if it exists
    unlink(file_foo);
  }

  // Rename original file
  ESP_LOGI(TAG, "Renaming file %s to %s", file_hello, file_foo);
  if (rename(file_hello, file_foo) != 0) {
    ESP_LOGE(TAG, "Rename failed");
    return;
  }

  ret = s_example_read_file(file_foo);
  if (ret != ESP_OK) {
    return;
  }

  const char *file_nihao = SD_MOUNT "/nihao.txt";
  memset(data, 0, EXAMPLE_MAX_CHAR_SIZE);
  // snprintf(data, EXAMPLE_MAX_CHAR_SIZE, "%s %s!\n", "Nihao", card->cid.name);
  source = "Nihou";
  ret = s_example_write_file(file_nihao, source);
  if (ret != ESP_OK) {
    return;
  }

  // Open file for reading
  ret = s_example_read_file(file_nihao);
  if (ret != ESP_OK) {
    return;
  }
}