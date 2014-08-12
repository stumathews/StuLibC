typedef struct {
    int size;
    void **keys;
    void **values;
} Hash;

Hash *hash_new (int size) {
    Hash *hash = calloc(1, sizeof (Hash));
    hash->size = size;
    hash->keys = calloc(size, sizeof (void *));
    hash->values = calloc(size, sizeof (void *));
    return hash;
}

int hash_index (Hash *hash, void *key) {
    int index = (int) key % hash->size;
    while (hash->keys[index] && hash->keys[index] != key)
        index = (index + 1) % hash->size;
    return index;
}

void hash_insert (Hash *hash, void *key, void *value) {
    int index = hash_index(hash, key);
    hash->keys[index] = key;
    hash->values[index] = value;
}

void *hash_lookup (Hash *hash, void *key) {
    int index = hash_index(hash, key);
    return hash->values[index];
}
