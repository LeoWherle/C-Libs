# Compilation of my old C libraries

```sh
language : C
compilation : via Makefile, including re, clean and fclean rules
```

# The libraries include the following:

## 1. Buffer (buffer)

### 1.1 Vectors

```c
typedef void (*dtor_t)(void *);
typedef void (*cpctor_t)(void *, const void *);

struct vector_s {
    void *items;
    size_t nmemb;
    size_t capacity;
    size_t item_size;
    dtor_t dtor;
    cpctor_t cpctor;
};
```

- Conversion to json [(header)](buffer/include/vector/json.h)
- pre-allocation
- tons of functions [(header)](buffer/include/vector.h)
- Macros for ease of use [(discouraged for most of them)](buffer/include/vector/macros.h)
- Unit tested

### 1.2 Arrays

They are just vectors of `char`s, (wich is not the best idea)

## 2. Circular Buffer (cbuffer)

```c
typedef struct cbuffer_s {
    char *data;
    size_t size;
} cbuffer_t;
```

- Fixed size
- Basic manipulations

## 3. Chained Lists (clist)

```c
struct node_s {
    void *data;
    struct node_s *next;
    struct node_s *prev;
};

struct list_s {
    struct node_s *head;
    struct node_s *tail;
    uint32_t size;
};
```

- Basic manipulations
- compatibilty with C strings
- Unit tested

## 4. Logging library (serrorh)

```c
LOG_ERROR("not enough items: %s", somevariable);
DEBUG_ASSERT(1 == 4);
```

- environnement file support
- load display level from environnement
- minimum displayed logging level
- changeable logging level at runtime
- changeable color at runtime
