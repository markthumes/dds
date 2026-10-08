# dds
LUT Based Direct Digital Synthesis
<img width="929" height="582" alt="image" src="https://github.com/user-attachments/assets/14d5b379-e612-4803-bbf1-a0fc0d7e3a16" />
<img width="1187" height="1038" alt="image" src="https://github.com/user-attachments/assets/b3556891-79a1-44dc-9263-2d18c99b829e" />

~~~~~~~~~~~~
1. CLB Logic
------------

+-------------------------+------+-------+------------+-----------+-------+
|        Site Type        | Used | Fixed | Prohibited | Available | Util% |
+-------------------------+------+-------+------------+-----------+-------+
| CLB LUTs*               |   32 |     0 |          0 |   1182240 | <0.01 |
|   LUT as Logic          |   32 |     0 |          0 |   1182240 | <0.01 |
|   LUT as Memory         |    0 |     0 |          0 |    591840 |  0.00 |
| CLB Registers           |   11 |     0 |          0 |   2364480 | <0.01 |
|   Register as Flip Flop |   11 |     0 |          0 |   2364480 | <0.01 |
|   Register as Latch     |    0 |     0 |          0 |   2364480 |  0.00 |
| CARRY8                  |    6 |     0 |          0 |    147780 | <0.01 |
| F7 Muxes                |    0 |     0 |          0 |    591120 |  0.00 |
| F8 Muxes                |    0 |     0 |          0 |    295560 |  0.00 |
| F9 Muxes                |    0 |     0 |          0 |    147780 |  0.00 |
+-------------------------+------+-------+------------+-----------+-------+
* Warning! The Final LUT count, after physical optimizations and full implementation, is typically lower. Run opt_design after synthesis, if not already completed, for a more realistic count.
Warning! LUT value is adjusted to account for LUT combining.
Warning! For any ECO changes, please run place_design if there are unplaced instances

2. BLOCKRAM
-----------

+-------------------+------+-------+------------+-----------+-------+
|     Site Type     | Used | Fixed | Prohibited | Available | Util% |
+-------------------+------+-------+------------+-----------+-------+
| Block RAM Tile    |    1 |     0 |          0 |      2160 |  0.05 |
|   RAMB36/FIFO*    |    1 |     0 |          0 |      2160 |  0.05 |
|     RAMB36E2 only |    1 |       |            |           |       |
|   RAMB18          |    0 |     0 |          0 |      4320 |  0.00 |
| URAM              |    0 |     0 |          0 |       960 |  0.00 |
+-------------------+------+-------+------------+-----------+-------+
* Note: Each Block RAM Tile only has one FIFO logic available and therefore can accommodate only one FIFO36E2 or one FIFO18E2. However, if a FIFO18E2 occupies a Block RAM Tile, that tile can still accommodate a RAMB18E2

* 8. Primitives
-------------

+----------+------+---------------------+
| Ref Name | Used | Functional Category |
+----------+------+---------------------+
| OBUF     |   32 |                 I/O |
| LUT2     |   29 |                 CLB |
| INBUF    |   23 |                 I/O |
| IBUFCTRL |   23 |              Others |
| FDRE     |   11 |            Register |
| CARRY8   |    6 |                 CLB |
| LUT3     |    2 |                 CLB |
| RAMB36E2 |    1 |            BLOCKRAM |
| LUT1     |    1 |                 CLB |
| BUFGCE   |    1 |               Clock |
+----------+------+---------------------+

~~~~~~~~~~~~
