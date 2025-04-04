#pragma once

namespace my {

template <typename T>
class shared_ptr {
private:
    // Holds a pointer to managed object (template class)
    T* obj_ptr;
    // Holds a pointer to shared control block with 2 counters and a deleter:
    // * shared_refs count (as `std::atomic<size_t>`)
    // * weak_refs count (as `std::atomic<size_t>`)
    // * deleter (function pointer)
    struct ControlBlock {
        std::atomic<size_t> shared_refs;
        std::atomic<size_t> weak_refs;
        void (*deleter)(T*);

        ControlBlock()
            : shared_refs(1), weak_refs(0), deleter(nullptr) {}
    };
    ControlBlock* control_block_ptr;

public:
    // Constructor: copies a pointer and allocate the control block
    shared_ptr(T* pointer = nullptr) {
        obj_ptr = pointer;
        control_block_ptr = new ControlBlock();
    }
    // Destructor: decrease shared_refs and:
    // - if shared_refs == 0 -> release the managed object
    // - if shared_refs == 0 and weak_refs == 0 -> release the control block
    ~shared_ptr() {
        if (control_block_ptr) {
            control_block_ptr->shared_refs--;
            if (0 == control_block_ptr->shared_refs) {
                if (control_block_ptr->deleter) {
                    control_block_ptr->deleter(obj_ptr);
                } else {
                    delete obj_ptr;
                }
                if (0 == control_block_ptr->weak_refs) {
                    delete control_block_ptr;
                }
            }
        }
    }
    // Copying is allowed - it increments shared_refs
    shared_ptr(const shared_ptr& other) {
        obj_ptr = other.obj_ptr;

        other.control_block_ptr->shared_refs++;
        control_block_ptr = other.control_block_ptr;
    }
    shared_ptr& operator=(const shared_ptr& other) {
        obj_ptr = other.obj_ptr;

        other.control_block_ptr->shared_refs++;
        control_block_ptr = other.control_block_ptr;

        return *this;
    }
    // Moving is allowed and it means:
    //   * Copying original pointers to a new object
    //   * Setting source pointer to nullptr
    shared_ptr(shared_ptr&& other) {
        obj_ptr = other.obj_ptr;
        control_block_ptr = other.control_block_ptr;
        other.obj_ptr = nullptr;
        other.control_block_ptr = nullptr;
    }
    shared_ptr& operator=(shared_ptr&& other) {
        obj_ptr = other.obj_ptr;
        control_block_ptr = other.control_block_ptr;
        other.obj_ptr = nullptr;
        other.control_block_ptr = nullptr;
        return *this;
    }

    size_t use_count() {
        if (control_block_ptr) {
            return control_block_ptr->shared_refs;
        } else {
            return 0;
        }
    }

    T& operator*() {
        return *obj_ptr;
    }

    T* operator->() {
        return obj_ptr;
    }

    explicit operator bool() const {
        return obj_ptr != nullptr;
    }

    T* get() {
        return obj_ptr;
    }
    
    void reset(T* new_ptr = nullptr) {
        if (obj_ptr != new_ptr) {
            if (control_block_ptr) {
                control_block_ptr->shared_refs--;
                if (0 == control_block_ptr->shared_refs) {
                    if (control_block_ptr->deleter) {
                        control_block_ptr->deleter(obj_ptr);
                    } else {
                        delete obj_ptr;
                    }
                    if (0 == control_block_ptr->weak_refs) {
                        delete control_block_ptr;
                    }
                }
            }
            obj_ptr = new_ptr;
            if (new_ptr) {
                control_block_ptr = new ControlBlock();
            } else {
                control_block_ptr = nullptr;
            }
        }
    }
};

}  // namespace my
