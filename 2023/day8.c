#include "stdio.h"
#include "string.h"

typedef char bool;
const bool true = 1;
const bool false = 0;

int node_value(char *node) {
    int value = 0;
    for (int i = 0; i < 3; i++) {
        value *= 26; value += node[i] - 'A';
    }
    return value;
}

typedef struct Node {
    int left; int right; bool ends_with_z;
} Node;

typedef struct NodePathData {
    unsigned long long int z_indices[8];
    int final_node;
} NodePathData;

void set_z_index(NodePathData *node, int index) {
    node->z_indices[index >> 6] |= (1 << (index & 63));
}

int main(int argc, char **argv) {

    char name[4], left[4], right[4];

    char path[1000];
    scanf("%999s\n\n", path);
    const int path_length = strlen(path);

    // I don't feel like implementing a proper hash table
    int node_indices[27000];
    Node nodes[1000];
    int num_nodes = 0;

    int starting_nodes[1000];
    int num_starting_nodes = 0;

    while (scanf("%3s = (%3s, %3s)\n", name, left, right) == 3) {
        int name_value = node_value(name);
        node_indices[name_value] = num_nodes;

        nodes[num_nodes].left = node_value(left);
        nodes[num_nodes].right = node_value(right);
        nodes[num_nodes].ends_with_z = name[2] == 'Z';

        if (name[2] == 'A') {
            starting_nodes[num_starting_nodes++] = num_nodes;
        }

        num_nodes++;
    }

    for (int i = 0; i < num_nodes; i++) {
        nodes[i].left = node_indices[nodes[i].left];
        nodes[i].right = node_indices[nodes[i].right];
    }

    NodePathData visit_data[1000];
    for (int i = 0; i < num_nodes; i++) {
        memset(visit_data[i].z_indices, 0, 64);
        int node = i;
        for (int j = 0; path[j]; j++) {
            if (nodes[node].ends_with_z) {
                set_z_index(visit_data + i, j);
            }
            if (path[j] == 'L') {
                node = nodes[node].left;
            }
            else {
                node = nodes[node].right;
            }
        }
        visit_data[i].final_node = node;
    }

    bool converged = false;
    int converged_to;
    unsigned long long int num_cycles = 0;
    int indices[1000];
    while (!converged) {
        for (int i = 0; i < (path_length + 63) / 64; i++) {
            unsigned long long int z_indices = ~0ull;
            for (int j = 0; j < num_starting_nodes; j++) {
                z_indices &= visit_data[starting_nodes[j]].z_indices[i];
            }

            if (z_indices == 0) continue;
            for (int j = 0; j < 64; j++) {
                if (z_indices & (1 << j)) {
                    converged = true;
                    converged_to = (i << 6) + j;
                    break;
                }
            }
            break;
        }
        if (converged) break;

        for (int i = 0; i < num_starting_nodes; i++) {
            starting_nodes[i] = visit_data[starting_nodes[i]].final_node;
        }

        num_cycles++;
    }

    unsigned long long int answer = num_cycles;
    answer *= path_length;
    answer += converged_to;

    printf("Num cycles:\t%llu\nConverged to:\t%d\nAnswer:\t\t%lld\n", num_cycles, converged_to, answer);
    return 0;
}
