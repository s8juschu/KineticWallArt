from django.db import models
from colorfield.fields import ColorField


class Animation(models.Model):
    name = models.CharField(max_length=10)


class Pattern(models.Model):
    name = models.CharField(max_length=100)
    # Relation to animation, optional
    animation = models.ForeignKey(Animation, blank=True, null=True, on_delete=models.CASCADE)


class Cross(models.Model):
    name = models.CharField(max_length=100)
    illumination = models.BooleanField()
    ill_cross1 = models.BooleanField()
    ill_cross2 = models.BooleanField()
    ill_cross3 = models.BooleanField()
    ill_cross4 = models.BooleanField()
    color_cross1 = ColorField(default='#ffffff')
    color_cross2 = ColorField(default='#ffffff')
    color_cross3 = ColorField(default='#ffffff')
    color_cross4 = ColorField(default='#ffffff')
    rotation = models.IntegerField(default=0)
    pattern = models.ForeignKey(Pattern, on_delete=models.CASCADE)
