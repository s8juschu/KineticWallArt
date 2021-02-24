from django.db import models
from colorfield.fields import ColorField

# Create your models here.
# class MyModel(models.Model):
#     color = ColorField(default='#FF0000')


class Pattern(models.Model):
    name = models.CharField(max_length=100)


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


class Animation(models.Model):
    name = models.CharField(max_length=10)
