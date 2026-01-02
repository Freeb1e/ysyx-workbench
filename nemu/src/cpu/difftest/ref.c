/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/cpu.h>
#include <difftest-def.h>
#include <memory/paddr.h>

__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
  if (direction == DIFFTEST_TO_REF) {
    // NPC -> NEMU: 把 buf 里的数据写入 NEMU 的物理内存 addr 处
    // 这是一个逐字节拷贝的例子，也可以用 paddr_write 循环
    uint8_t *byte_buf = (uint8_t *)buf;
    for (size_t i = 0; i < n; i++) {
        paddr_write(addr + i, 1, byte_buf[i]); 
    }
  } else {
    // NEMU -> NPC: 把 NEMU 物理内存 addr 处的数据读到 buf 里
    uint8_t *byte_buf = (uint8_t *)buf;
    for (size_t i = 0; i < n; i++) {
        byte_buf[i] = paddr_read(addr + i, 1);
    }
  }
}

__EXPORT void difftest_regcpy(void *dut, bool direction) {

  if (direction == DIFFTEST_TO_REF) {
    // NPC -> NEMU: 强制让 NEMU 的寄存器等于传入的值
    cpu = *(CPU_state *)dut; 
  } else {
    // NEMU -> NPC: 把 NEMU 当前的寄存器状态拷给外部
    *(CPU_state *)dut = cpu;
  }
}

__EXPORT void difftest_exec(uint64_t n) {
  cpu_exec(n);
}

__EXPORT void difftest_raise_intr(word_t NO) {
  assert(0);
}

__EXPORT void difftest_init(int port) {
  void init_mem();
  init_mem();
  /* Perform ISA dependent initialization. */
  init_isa();
}
