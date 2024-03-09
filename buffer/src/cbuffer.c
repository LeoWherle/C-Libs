#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <stdio.h>

#define BUFFER_SIZE 4096 // Must be a multiple of page size

typedef struct {
  void* data;
  size_t size;
  size_t read_offset;
  size_t write_offset;
} circular_buffer_t;

circular_buffer_t* create_buffer() {
  circular_buffer_t* buffer = malloc(sizeof(circular_buffer_t));
  buffer->data = mmap(NULL, BUFFER_SIZE * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (buffer->data == MAP_FAILED) {
    perror("mmap");
    return NULL;
  }
  buffer->size = BUFFER_SIZE;
  buffer->read_offset = 0;
  buffer->write_offset = 0;
  return buffer;
}

void write_data(circular_buffer_t* buffer, void* data, size_t data_size) {
  // Handle cases where data wraps around
  if (buffer->write_offset + data_size > buffer->size) {
    size_t first_part = buffer->size - buffer->write_offset;
    memcpy(buffer->data + buffer->write_offset, data, first_part);
    memcpy(buffer->data, (char*)data + first_part, data_size - first_part);
    // Adjust offsets for wrap-around
    buffer->write_offset = data_size - first_part;
  } else {
    memcpy(buffer->data + buffer->write_offset, data, data_size);
    buffer->write_offset += data_size;
  }
}

// Similar logic can be implemented for read operation

void destroy_buffer(circular_buffer_t* buffer) {
  munmap(buffer->data, BUFFER_SIZE * 2);
  free(buffer);
}

int main() {
  circular_buffer_t* buffer = create_buffer();
  // Write and read operations using write_data and similar read function
  destroy_buffer(buffer);
  return 0;
}
