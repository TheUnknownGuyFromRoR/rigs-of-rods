/*
	This source file is part of Rigs of Rods
	Copyright 2005-2012 Pierre-Michel Ricordel
	Copyright 2007-2012 Thomas Fischer
	Copyright 2013-2014 Petr Ohlidal

	For more information, see http://www.rigsofrods.com/

	Rigs of Rods is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License version 3, as
	published by the Free Software Foundation.

	Rigs of Rods is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Rigs of Rods.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
	@file   RigDef_File.cpp
	@author Petr Ohlidal
	@date   12/2013
*/

#include "RigDef_File.h"

namespace RigDef
{
#ifndef _WIN32
	/* These definitions are needed because the variables are declared but not defined in Axle */
	const char Axle::OPTION_o_OPEN;
	const char Axle::OPTION_l_LOCKED;
	const char Axle::OPTION_s_SPLIT;
#endif // !_WIN32

/* -------------------------------------------------------------------------- */
/* Sections                                                                   */
/*                                                                            */
/* This is the place to set defaults.                                         */
/* -------------------------------------------------------------------------- */

Airbrake::Airbrake():
	offset(Ogre::Vector3::ZERO),
	width(0),
	height(0),
	max_inclination_angle(0),
	texcoord_x1(0),
	texcoord_x2(0),
	texcoord_y1(0),
	texcoord_y2(0),
	lift_coefficient(1.f) // This is default
{}

AntiLockBrakes::AntiLockBrakes():
	regulation_force(0),
	min_speed(0),
	pulse_per_sec(0),
	mode(MODE_ON),
	_pulse_per_sec_set(false)
{}

Command2::Command2():
	shorten_rate(0),
	lengthen_rate(0),
	max_contraction(0),
	max_extension(0),
	contract_key(0),
	extend_key(0),
	options(0),
	_format_version(1), /* 1 = 'commands', 2 = 'commands2' */
	affect_engine(1),
	detacher_group(0),
	needs_engine(true)
{}

Engoption::Engoption():
	inertia(10.f),
	clutch_force(0.f), /* Default = 10000 for trucks, 5000 for cars */
	_clutch_force_use_default(true),
	shift_time(0.2f),
	clutch_time(0.5f),
	type(ENGINE_TYPE_t_TRUCK),
	post_shift_time(0.2f),
	idle_rpm(-1.f),
	stall_rpm(-1.f),
	max_idle_mixture(0.2f),
	min_idle_mixture(0.f) /* This is a default */
{}

Fusedrag::Fusedrag():
	autocalc(false),
	approximate_width(0),
	area_coefficient(0),
	_area_coefficient_set(false),
	airfoil_name("NACA0009.afl")
{}

Hook::Hook():
	flags(0),
	option_hook_range(0.4f),
	option_speed_coef(1.0f),
	option_max_force(10000000.f), // HOOK_FORCE_DEFAULT
	option_hookgroup(-1),
	option_lockgroup(-1),
	option_timer(5.f),
	option_minimum_range_meters(0.f)
{}

NodeDefaults::NodeDefaults():
	load_weight(-1.f),
	friction(1),
	volume(1),
	surface(1),
	options(0)
{}

Shock::Shock():
	spring_rate(0),
	damping(0),
	short_bound(0),
	long_bound(0),
	precompression(1),
	options(0),
	detacher_group(0)
{}

Shock2::Shock2():
	spring_in(0),
	damp_in(0),
	progress_factor_spring_in(0),
	progress_factor_damp_in(0),
	spring_out(0),
	damp_out(0),
	progress_factor_spring_out(0),
	progress_factor_damp_out(0),
	short_bound(0),
	long_bound(0),
	precompression(0),
	options(0),
	detacher_group(0)
{}

SlideNode::SlideNode():
	spring_rate(9000000),
	break_force(0),
	tolerance(0),
	railgroup_id(0),
	_railgroup_id_set(false),
	attachment_rate(1.f),
	max_attachment_distance(0.1f),
	constraint_flags(0),
	_break_force_set(false)
{
	rail_node_ranges.reserve(25);
}

Tie::Tie():
	max_reach_length(0),
	auto_shorten_rate(0),
	min_length(0),
	max_length(0),
	options(OPTIONS_VISIBLE),
	max_stress(100000.0f), // default, hardcoded in legacy SerializedRig.cpp, BTS_TIES
	detacher_group(0), /* Global detacher group */
	group(-1), // default value
	_group_set(false)
{}

TractionControl::TractionControl():
	regulation_force(0),
	wheel_slip(0),
	fade_speed(0),
	pulse_per_sec(0),
	mode(0)
{}

Trigger::Trigger():
	shortbound_trigger_key(0),
	longbound_trigger_key(0),
	contraction_trigger_limit(0),
	expansion_trigger_limit(0),
	options(0),
	boundary_timer(1.f), /* Default */
	_engine_trigger_motor_index(0),
	_engine_trigger_function(ENGINE_TRIGGER_FUNCTION_INVALID),
	detacher_group(0)
{}

VideoCamera::VideoCamera():
	_alt_reference_node_set(false),
	_alt_orientation_node_set(false),
	offset(Ogre::Vector3::ZERO),
	rotation(Ogre::Vector3::ZERO),
	field_of_view(0),
	texture_width(0),
	texture_height(0),
	min_clip_distance(0),
	max_clip_distance(0),
	camera_role(0),
	camera_mode(0)
{}

Wing::Wing():
	control_surface(CONTROL_n_NONE),
	chord_point(-1.f),
	min_deflection(-1.f),
	max_deflection(-1.f),
	efficacy_coef(1.f) // So-called 'liftcoef'. Default = 1
{
	tex_coords[0] = 0.f;
	tex_coords[1] = 0.f;
	tex_coords[2] = 0.f;
	tex_coords[3] = 0.f;
	tex_coords[4] = 0.f;
	tex_coords[5] = 0.f;
	tex_coords[6] = 0.f;
	tex_coords[7] = 0.f;
}

/* -------------------------------------------------------------------------- */
/* File
/* -------------------------------------------------------------------------- */

const char * File::SectionToString(File::Section section)
{
	switch (section)
	{
		case (File::SECTION_AIRBRAKES):
			return "airbrakes";
		case (File::SECTION_ANIMATORS):
			return "animators";
		case (File::SECTION_ANTI_LOCK_BRAKES):
			return "AntiLockBrakes";
		case (File::SECTION_AUTHOR):
			return "author";
		case (File::SECTION_AXLES):
			return "axles";
		case (File::SECTION_BEAMS):
			return "beams";
		case (File::SECTION_BRAKES):
			return "brakes";
		case (File::SECTION_CAMERAS):
			return "cameras";
		case (File::SECTION_CAMERA_RAIL):
			return "camerarail";
		case (File::SECTION_CINECAM):
			return "cinecam";
		case (File::SECTION_COLLISION_BOXES):
			return "collisionboxes";
		case (File::SECTION_COMMANDS):
			return "commands";
		case (File::SECTION_COMMANDS_2):
			return "commands2";
		case (File::SECTION_CONTACTERS):
			return "contacters";
		case (File::SECTION_ENGINE):
			return "engine";
		case (File::SECTION_ENGOPTION):
			return "engoption";
		case (File::SECTION_EXHAUSTS):
			return "exhausts";
		case (File::SECTION_FIXES):
			return "fixes";
		case (File::SECTION_FLARES):
			return "flares";
		case (File::SECTION_FLARES_2):
			return "flares2";
		case (File::SECTION_FLEXBODIES):
			return "flexbodies";
		case (File::SECTION_FLEX_BODY_WHEELS):
			return "flexbodywheels";
		case (File::SECTION_FUSEDRAG):
			return "fusedrag";
		case (File::SECTION_GLOBALS):
			return "globals";
		case (File::SECTION_GUI_SETTINGS):
			return "guisettings";
		case (File::SECTION_HYDROS):
			return "hydros";
		case (File::SECTION_HELP):
			return "help";
		case (File::SECTION_HOOKS):
			return "hooks";
		case (File::SECTION_LOCKGROUPS):
			return "lockgroups";
		case (File::SECTION_MANAGED_MATERIALS):
			return "managedmaterials";
		case (File::SECTION_MATERIAL_FLARE_BINDINGS):
			return "materialflarebindings";
		case (File::SECTION_MESH_WHEELS):
			return "meshwheels";
		case (File::SECTION_MESH_WHEELS_2):
			return "meshwheels2";
		case (File::SECTION_MINIMASS):
			return "minimass";
		case (File::SECTION_NODES):
			return "nodes";
		case (File::SECTION_NODES_2):
			return "nodes2";
		case (File::SECTION_PARTICLES):
			return "particles";
		case (File::SECTION_PISTONPROPS):
			return "pistonprops";
		case (File::SECTION_PROPS):
			return "props";
		case (File::SECTION_RAILGROUPS):
			return "railgroups";
		case (File::SECTION_ROPABLES):
			return "ropables";
		case (File::SECTION_ROPES):
			return "ropes";
		case (File::SECTION_ROTATORS):
			return "rotators";
		case (File::SECTION_ROTATORS_2):
			return "rotators_2";
		case (File::SECTION_SCREWPROPS):
			return "screwprops";
		case (File::SECTION_SHOCKS):
			return "shocks";
		case (File::SECTION_SHOCKS_2):
			return "shocks2";
		case (File::SECTION_SLIDENODES):
			return "slidenodes";
		case (File::SECTION_SOUNDSOURCES):
			return "soundsources";
		case (File::SECTION_SOUNDSOURCES2):
			return "soundsources2";
		case (File::SECTION_SLOPE_BRAKE):
			return "SlopeBrake";
		case (File::SECTION_TIES):
			return "ties";
		case (File::SECTION_TORQUE_CURVE):
			return "torquecurve";
		case (File::SECTION_TRACTION_CONTROL):
			return "TractionControl";
		case (File::SECTION_TRIGGERS):
			return "triggers";
		case (File::SECTION_TRUCK_NAME):
			return "<truck name>";
		case (File::SECTION_TURBOJETS):
			return "turbojets";
		case (File::SECTION_TURBOPROPS):
			return "turboprops";
		case (File::SECTION_TURBOPROPS_2):
			return "turboprops";
		case (File::SECTION_VIDEO_CAMERA):
			return "videocamera";
		case (File::SECTION_WHEELS):
			return "wheels";
		case (File::SECTION_WHEELS_2):
			return "wheels2";
		case (File::SECTION_WINGS):
			return "wings";

		case (File::SECTION_NONE):
			return "SECTION_NONE";
		default: 
			return "<unknown>";
	}
}

const char * File::SubsectionToString(File::Subsection subsection)
{
	switch (subsection)
	{
		case (File::SUBSECTION_NONE):
			return "SUBSECTION_NONE";
		case (File::SUBSECTION__FLEXBODIES__PROPLIKE_LINE):
			return "SUBSECTION_PROPLIKE_LINE";
		case (File::SUBSECTION__FLEXBODIES__FORSET_LINE):
			return "SUBSECTION_FORSET_LINE";
		case (File::SUBSECTION__SUBMESH__TEXCOORDS):
			return "SUBSECTION_TEXCOORDS";
		case (File::SUBSECTION__SUBMESH__CAB):
			return "SUBSECTION_CAB";
		default:
			return "~ UNKNOWN SUBSECTION ~";
	}
}

const char * File::KeywordToString(File::Keyword keyword)
{
	/* NOTE: Maintain alphabetical order! */

	switch (keyword)
	{
		case (File::KEYWORD_AIRBRAKES):
			return "airbrakes";
		case (File::KEYWORD_ANIMATORS):
			return "animators";
		case (File::KEYWORD_ANTI_LOCK_BRAKES):
			return "AntiLockBrakes";
		case (File::KEYWORD_AUTHOR):
			return "author";
		case (File::KEYWORD_AXLES):
			return "axles";
		case (File::KEYWORD_BEAMS):
			return "beams";
		case (File::KEYWORD_BRAKES):
			return "brakes";
		case (File::KEYWORD_CAMERAS):
			return "cameras";
		case (File::KEYWORD_CAMERARAIL):
			return "camerarail";
		case (File::KEYWORD_CINECAM):
			return "cinecam";
		case (File::KEYWORD_COLLISIONBOXES):
			return "collisionboxes";
		case (File::KEYWORD_COMMANDS):
			return "commands";
		case (File::KEYWORD_COMMANDS2):
			return "commands2";
		case (File::KEYWORD_CONTACTERS):
			return "contacters";
		case (File::KEYWORD_CRUISECONTROL):
			return "cruisecontrol";
		case (File::KEYWORD_ENGINE):
			return "engine";
		case (File::KEYWORD_ENGOPTION):
			return "engoption";
		case (File::KEYWORD_EXHAUSTS):
			return "exhausts";
		case (File::KEYWORD_FIXES):
			return "fixes";
		case (File::KEYWORD_FLARES):
			return "flares";
		case (File::KEYWORD_FLARES2):
			return "flares2";
		case (File::KEYWORD_FLEXBODIES):
			return "flexbodies";
		case (File::KEYWORD_FLEXBODYWHEELS):
			return "flexbodywheels";
		case (File::KEYWORD_FUSEDRAG):
			return "fusedrag";
		case (File::KEYWORD_GLOBALS):
			return "globals";
		case (File::KEYWORD_GUISETTINGS):
			return "guisettings";
		case (File::KEYWORD_HELP):
			return "help";
		case (File::KEYWORD_HOOKS):
			return "hooks";
		case (File::KEYWORD_HYDROS):
			return "hydros";
		case (File::KEYWORD_MANAGEDMATERIALS):
			return "managedmaterials";
		case (File::KEYWORD_MATERIALFLAREBINDINGS):
			return "materialflarebindings";
		case (File::KEYWORD_MESHWHEELS):
			return "meshwheels";
		case (File::KEYWORD_MESHWHEELS2):
			return "meshwheels2";
		case (File::KEYWORD_MINIMASS):
			return "minimass";
		case (File::KEYWORD_NODES):
			return "nodecollision";
		case (File::KEYWORD_NODES2):
			return "nodes2";
		case (File::KEYWORD_PARTICLES):
			return "particles";
		case (File::KEYWORD_PISTONPROPS):
			return "pistonprops";
		case (File::KEYWORD_PROPS):
			return "props";
		case (File::KEYWORD_RAILGROUPS):
			return "railgroups";
		case (File::KEYWORD_ROPABLES):
			return "ropables";
		case (File::KEYWORD_ROPES):
			return "ropes";
		case (File::KEYWORD_ROTATORS):
			return "rotators";
		case (File::KEYWORD_ROTATORS2):
			return "rotators_2";
		case (File::KEYWORD_SCREWPROPS):
			return "screwprops";
		case (File::KEYWORD_SHOCKS):
			return "shocks";
		case (File::KEYWORD_SHOCKS2):
			return "shocks2";
		case (File::KEYWORD_SLIDENODES):
			return "slidenodes";
		case (File::KEYWORD_SLOPE_BRAKE):
			return "SlopeBrake";
		case (File::KEYWORD_SOUNDSOURCES):
			return "soundsources";
		case (File::KEYWORD_SOUNDSOURCES2):
			return "soundsources2";
		case (File::KEYWORD_TIES):
			return "ties";
		case (File::KEYWORD_TORQUECURVE):
			return "torquecurve";
		case (File::KEYWORD_TRACTION_CONTROL):
			return "TractionControl";
		case (File::KEYWORD_TRIGGERS):
			return "triggers";
		case (File::KEYWORD_TURBOJETS):
			return "turbojets";
		case (File::KEYWORD_TURBOPROPS):
			return "turboprops";
		case (File::KEYWORD_TURBOPROPS2):
			return "turboprops2";
		case (File::KEYWORD_VIDEOCAMERA):
			return "videocamera";
		case (File::KEYWORD_WHEELS):
			return "wheels";
		case (File::KEYWORD_WHEELS2):
			return "wheels2";
		case (File::KEYWORD_WINGS):
			return "wings";

		default: 
			return "~Unknown~";
	}
}

File::Module::Module(Ogre::String const & name):
	name(name)
{
	/* Pre-allocate */
	airbrakes.reserve(10);
	animators.reserve(50);
	axles.reserve(10);
	beams.reserve(1000);
	cameras.reserve(10);
	camera_rails.reserve(10);
	collision_boxes.reserve(10);
	commands_2.reserve(35);
	exhausts.reserve(6);
	flares_2.reserve(10);
	flexbodies.reserve(15);
	hooks.reserve(10);
	hydros.reserve(25);
	lockgroups.reserve(10);
	managed_materials.reserve(25);
	material_flare_bindings.reserve(10);
	mesh_wheels.reserve(10);
	mesh_wheels_2.reserve(10);
	nodes.reserve(2000);
	node_collisions.reserve(100);
	particles.reserve(25);
	pistonprops.reserve(25);
	props.reserve(50);
	railgroups.reserve(10);
	ropables.reserve(50);
	ropes.reserve(25);
	rotators.reserve(15);
	rotators_2.reserve(15);
	screwprops.reserve(10);
	shocks.reserve(50);
	shocks_2.reserve(50);
	slidenodes.reserve(25);
	soundsources.reserve(20);
	soundsources2.reserve(20);
	submeshes.reserve(50);
	ties.reserve(25);
	triggers.reserve(25);
	turbojets.reserve(15);
	turboprops_2.reserve(15);
	videocameras.reserve(10);	
	wheels.reserve(6);
	wheels_2.reserve(8);
	wings.reserve(10);
}

File::File():
	file_format_version(0), // Default = unset
	hide_in_chooser(false),
	enable_advanced_deformation(false),
	rollon(false),
	forward_commands(false),
	import_commands(false),
	lockgroup_default_nolock(false),
	rescuer(false),
	disable_default_sounds(false),
	slide_nodes_connect_instantly(false),
	collision_range(0),
	_collision_range_set(false),
	minimum_mass(0.f),
	_minimum_mass_set(false)
{
	authors.reserve(10);	
	description.reserve(20);
}

} /* namespace RigDef */
