{
  description = "Nix devshell for OpenGL development";

  inputs = { 
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
  };

  outputs = { self, nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.x86_64-linux.default = pkgs.mkShell.override {
          stdenv = pkgs.clangStdenv;
        } 
        { 
        nativeBuildInputs = with pkgs; [
          clang
          cmake
          gnumake
          libclang
        ];
        buildInputs = with pkgs; [
          pkg-config
          glfw-wayland-minecraft
          imgui
        ];
        packages = with pkgs; [
          clang-tools
          python3
          mesa
          glxinfo
          lldb
          glsl_analyzer
        ];
        shellHook = ''
          export PATH=$PATH:${pkgs.clang-tools}/bin
          export LD_LIBRARY_PATH="${pkgs.libclang}/resource-root/lib/linux:${pkgs.glfw-wayland-minecraft}/lib:${pkgs.wayland}/lib:/run/opengl-driver/lib:/run/opengl-driver-32/lib"
          export IMGUI="${pkgs.imgui}"
        '';
      };
    };

}
