// Cyberdeck Fieldkit - Clamshell Case
// CC BY-NC-SA 4.0 - Neil Manfred
// Parametric skeleton: adjust dimensions to match final part sourcing,
// then re-export STL/3MF per half before printing.

/* ---------- Global parameters ---------- */
wall_t          = 3;      // shell wall thickness, mm
tolerance       = 0.3;    // fit clearance, mm

/* ---------- Lower half (base) ---------- */
base_w          = 260;
base_d          = 190;
base_h          = 28;

nuc_w           = 115;    // confirmed: GMKtec NucBox G3 barebone (115x108x44mm)
nuc_d           = 108;
nuc_h           = 44;

keyboard_w      = 245;    // 60-65% board footprint
keyboard_d      = 95;
keyboard_h      = 12;

module_bay_w    = 90;     // TODO: resize to LilyGO T-Embed CC1101 footprint once in hand
module_bay_d    = 60;
module_bay_h    = 18;

/* ---------- Upper half (lid) ---------- */
lid_w           = base_w;
lid_d           = base_d;
lid_h           = 14;

screen_w        = 118;    // per-panel, 5.5"-7" class - confirm against sourced panel
screen_d         = 75;
screen_gap      = 8;      // gap between the two panels

/* ---------- Hinge ---------- */
hinge_len       = base_w - 20;
hinge_dia       = 8;

/* ================= Modules ================= */

module shell(w, d, h, t = wall_t) {
    difference() {
        cube([w, d, h]);
        translate([t, t, t])
            cube([w - 2*t, d - 2*t, h]);
    }
}

module lower_half() {
    difference() {
        shell(base_w, base_d, base_h);

        // NUC bay
        translate([15, 15, wall_t])
            cube([nuc_w + tolerance, nuc_d + tolerance, nuc_h]);

        // Keyboard bay
        translate([15, base_d - keyboard_d - 15, wall_t])
            cube([keyboard_w, keyboard_d, keyboard_h]);

        // Embedded security module bay - front edge for sensor cutouts
        translate([base_w - module_bay_w - 15, 15, wall_t])
            cube([module_bay_w, module_bay_d, module_bay_h]);
    }
}

module upper_half() {
    difference() {
        shell(lid_w, lid_d, lid_h);

        // Screen 1
        translate([20, (lid_d - screen_d)/2, wall_t])
            cube([screen_w, screen_d, lid_h]);

        // Screen 2
        translate([20 + screen_w + screen_gap, (lid_d - screen_d)/2, wall_t])
            cube([screen_w, screen_d, lid_h]);
    }
}

module hinge() {
    translate([(base_w - hinge_len)/2, 0, 0])
        rotate([0, 90, 0])
            cylinder(h = hinge_len, d = hinge_dia, $fn = 32);
}

/* ================= Layout for preview ================= */
lower_half();
translate([0, 0, base_h + 40]) upper_half();
translate([0, -20, base_h]) color("gray") hinge();
