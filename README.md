# rmfo
Rmfo is a tool that makes recipe templates for the omi package manager.

# Usage
```bash
rmfo tree
```
```text
Created recipe template for: tree in packages/tree/package.toml using: make
```
or using meson/cmake:
```bash
rmfo tree --meson
```

```text
Created recipe template for: tree in packages/tree/package.toml using: meson
```

```bash
rmfo tree --cmake
```

```text
Created recipe template for: tree in packages/tree/package.toml using: cmake
```

# About Usage
The actual information inside each package template needs to be filled out and
needs to be tested with the latest version of omi before submitting it to omi-inventory.

# Install
```bash
git clone https://github.com/voltiksrc/rmfo.git
```
```bash
cd rmfo
```
```bash
meson setup build
```
```bash
meson compile -C build
```
```bash
sudo meson install -C build
```

# Status
It can make a basic template for now.

