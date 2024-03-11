## Compile pure Yul with solc

```bash
solc --strict-assembly --optimize --optimize-runs 2000 ./yul/HorseStoreYul.yul --bin | grep 60
```
