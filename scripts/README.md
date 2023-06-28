```sh
./zmk_run_docker.sh -s -v 3.2 --host-zmk-dir ~/Projects/zmk-urob/ --host-config-dir ~/Projects/zmk-config/
```
```sh
west build -d /workspace/zmk-config/build/left -b puchi_ble_v1 -- -DSHIELD=corne_left -DZMK_CONFIG=/workspace/zmk-config/config/
west build -d /workspace/zmk-config/build/right -b puchi_ble_v1 -- -DSHIELD=corne_right -DZMK_CONFIG=/workspace/zmk-config/config/
```
