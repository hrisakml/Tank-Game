{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    gcc
    gnumake
    cmake
    pkg-config
    sfml        # SFML 3
    clang-tools
    #geany
  ];
}
