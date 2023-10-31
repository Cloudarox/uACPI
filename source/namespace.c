#include <uacpi/internal/namespace.h>
#include <uacpi/kernel_api.h>

static struct uacpi_namespace_node g_root;

struct uacpi_namespace_node *uacpi_namespace_node_alloc(uacpi_object_name name)
{
    struct uacpi_namespace_node *ret;

    ret = uacpi_kernel_calloc(1, sizeof(*ret));
    if (uacpi_unlikely(ret == UACPI_NULL))
        return ret;

    ret->name = name;
    return ret;
}

void uacpi_namespace_node_free(struct uacpi_namespace_node *node)
{
    uacpi_kernel_free(node);
}

uacpi_status uacpi_node_install(
    struct uacpi_namespace_node *parent,
    struct uacpi_namespace_node *node
)
{
    struct uacpi_namespace_node *prev;

    if (parent == UACPI_NULL)
        parent = &g_root;

    prev = parent->child;
    parent->child = node;
    node->parent = parent;
    node->next = prev;

    return UACPI_STATUS_OK;
}

struct uacpi_namespace_node *uacpi_namespace_node_find(
    struct uacpi_namespace_node *parent,
    uacpi_object_name name
)
{
    if (parent == UACPI_NULL)
        parent = &g_root;

    struct uacpi_namespace_node *node = parent->child;

    while (node) {
        if (node->name.id == name.id)
            return node;

        node = node->next;
    }

    return UACPI_NULL;
}