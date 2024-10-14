#include "storage.h"

static esp_err_t s_example_write_file(const char *path, char *data) {
  ESP_LOGI(TAG, "Opening file %s", path);
  FILE *f = fopen(path, "w");
  if (f == NULL) {
    ESP_LOGE(TAG, "Failed to open file for writing");
    return ESP_FAIL;
  }
  fprintf(f, data);
  fclose(f);
  ESP_LOGI(TAG, "File written");

  return ESP_OK;
}

static esp_err_t s_example_read_file(const char *path) {
  ESP_LOGI(TAG, "Reading file %s", path);
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    ESP_LOGE(TAG, "Failed to open file for reading");
    return ESP_FAIL;
  }
  char line[EXAMPLE_MAX_CHAR_SIZE];
  fgets(line, sizeof(line), f);
  fclose(f);

  // strip newline
  char *pos = strchr(line, '\n');
  if (pos) {
    *pos = '\0';
  }
  ESP_LOGI(TAG, "Read from file: '%s'", line);

  return ESP_OK;
}

void storage_task(void) {
  esp_err_t ret;

  ESP_LOGI(TAG, "Filesystem mounted");

  // First create a file.
  const char *file_hello = SD_MOUNT "/hello.txt";
  char *source = "Hello";
  char data[EXAMPLE_MAX_CHAR_SIZE];
  strcpy(data, source);
  // snprintf(data, EXAMPLE_MAX_CHAR_SIZE, "%s %s!\n", "Hello", card->cid.name);
  printf("%s", data);
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
  printf("%s", data);
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