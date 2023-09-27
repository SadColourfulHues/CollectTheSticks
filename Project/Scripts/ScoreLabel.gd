extends Label

@export var game_state: GameState


func _ready() -> void:
	_on_score_updated(0)
	game_state.score_changed.connect(self._on_score_updated)


func _on_score_updated(score: int) -> void:
	self.text = "Score: %d" % score
