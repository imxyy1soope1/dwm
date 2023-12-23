{
  description = "dwm flake";
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { self
    , nixpkgs
    , flake-utils
    ,
    }:
    let
      overlay =
        final: prev: {
          dwm = prev.dwm.overrideAttrs (oldAttrs: {
            buildInputs = with final.pkgs; [
              xorg.libX11
              xorg.libXft
              xorg.libXinerama
              xorg.libxcb
              yajl
              gcc
            ];
            version = "master";
            src = ./.;
          });
        };
    in
    flake-utils.lib.eachDefaultSystem
      (
        system:
        let
          pkgs = import nixpkgs {
            inherit system;
            overlays = [
              self.overlays.default
            ];
          };
        in
        {
          packages.dwm = pkgs.dwm;
          packages.default = pkgs.dwm;
        }
      )
    // { overlays.default = overlay; };
}
