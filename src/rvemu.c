#include "rvemu.h"

void getmaps(void) {
    printf("pid is %d\n", getpid());
    char cmd[50] = {};
    sprintf(cmd, "rm -rf ./maps && cp /proc/%d/maps ./maps",getpid());
    system(cmd);
}

int main(int argc, char* argv[]) {
    assert(argc > 1);

    machine_t machine = {0};
    machine.cache = new_cache();
    machine_load_program(&machine, argv[1]);
    machine_setup(&machine, argc, argv);

    getmaps();
    // a7 syscall number
    // a0-a6 args
    while(true) {
        enum exit_reason_t reason = machine_step(&machine);
        assert(reason == ecall);
        u64 syscall = machine_get_gp_reg(&machine, a7);
        u64 ret = do_syscall(&machine, syscall);
        machine_set_gp_reg(&machine, a0, ret);
    }
    return 0;
}


