{
  description = "Dev Shell for OpenGL development";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in 
  {

    devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          clang-tools
          clang
          cmake
          gnumake
          glxinfo
          lldb
          glsl_analyzer
          glfw
          wayland
        ];

        shellHook = ''
          LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/run/opengl-driver/lib:/run/opengl-driver-32/lib"
          LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.glfw}/lib"
          LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.wayland}/lib"
          export LD_LIBRARY_PATH
        '';
      };

  };
}
